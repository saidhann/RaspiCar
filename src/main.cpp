#include <crow.h>  // Include Crow header
#include <pigpio.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <sonar.h>

#define GPIO_FREQUENCY 50 // engine and servo pwm frequency input
#define ENGINE_PIN 5 // pin for engine pwm
#define SERVO_PIN 18 // pin for servo pwm
#define TRIG_PIN 20  // trigger pin for US sensor
#define ECHO_PIN 19  // echo pin for US sensor
#define TIMEOUT_US 30000
// Define GPIO pin for PWM

// Global variable to track the current PWM percentage
int enginePercentage = 0;
int servoPercentage = 0;
std::mutex engineMutex; // Mutex to ensure thread-safe access to currentPWMPercentage
std::mutex servoMutex;

//Global variebles for US sensor
std::mutex ultrasonicMutex;
double currentDistance = 0.0;

//Global variebles for temperature sensor
std::mutex temperatureMutex;
double currentTemperature = 0.0;

void updateTemperature() {
    while(true) {
        //here sonsor reading
        {
            std::lock_guard lock(temperatureMutex);
            //here temperate update
        }
    }
}

void updateDistance() {
    std::cout << "Begining distance measure" << std::endl;
    Sonar sonar;
    sonar.init(TRIG_PIN, ECHO_PIN);

    double distance = sonar.distance(TIMEOUT_US);
    if (distance >= 0) {
        std::cout << "Distance: " << distance << " cm" << std::endl;
    } else {
        std::cerr << "Measurement failed." << std::endl;
    }

    currentDistance = distance;
}

int main() {
    // Initialize pigpio
    if (gpioInitialise() < 0) {
        std::cerr << "Failed to initialize pigpio!" << std::endl;
        return -1;
    }

    std::cout << "Starting libcamera-vid stream..." << std::endl;
    std::system("libcamera-vid -t 0 --inline --listen -o tcp://0.0.0.0:8554 &");

    // Set up PWM pin
    gpioSetMode(ENGINE_PIN, PI_OUTPUT);
    gpioSetPWMrange(ENGINE_PIN, 1024);
    gpioSetPWMfrequency(ENGINE_PIN, GPIO_FREQUENCY);
    gpioSetMode(SERVO_PIN, PI_OUTPUT);
    gpioSetPWMrange(SERVO_PIN, 1024);
    gpioSetPWMfrequency(SERVO_PIN, GPIO_FREQUENCY);

    //Ultrasonic sensor
    gpioSetMode(TRIG_PIN, PI_OUTPUT);
    gpioSetMode(ECHO, PI_INPUT);
    gpioWrite(TRIG_PIN, PI_LOW);
    std::thread ultrasonicSensorThread(updateDistance);
    ultrasonicSensorThread.detach();

    //Temperature sensor
    //here setup for tmp sensor
        //std::thread temperatureSensorThread(updateTemperature);
        //temperatureSensorThread.detach();

    // Crow web server
    crow::SimpleApp app;

    // POST route for /engine to set PWM value
    CROW_ROUTE(app, "/engine").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        try {
            // Parse the value from the request body
            auto body = crow::json::load(req.body);
            if (!body || !body.has("value")) {
                return crow::response(400, "Invalid request, 'value' is required.");
            }

            int pwmValue = body["value"].i();
            if (pwmValue < 0 || pwmValue > 100) {
                return crow::response(400, "Value must be between 0 and 100.");
            }
            // 70 - 80 - 90

            int dutyCycle = pwmValue / 5 + 70;

            // Set the PWM duty cycle on the GPIO pin
            gpioPWM(ENGINE_PIN, dutyCycle);

            // Update the global current PWM value
            {
                std::lock_guard<std::mutex> lock(engineMutex);
                enginePercentage = pwmValue;
            }

            std::ostringstream msg;
            msg << "PWM set to " << pwmValue << "% (Duty Cycle: " << dutyCycle << ").";
            return crow::response(200, msg.str());
        } catch (const std::exception& e) {
            return crow::response(500, std::string("Internal Server Error: ") + e.what());
        }
    });

    CROW_ROUTE(app, "/turn").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        try {
            // Parse the value from the request body
            auto body = crow::json::load(req.body);
            if (!body || !body.has("value")) {
                return crow::response(400, "Invalid request, 'value' is required.");
            }

            int pwmValue = body["value"].i();
            if (pwmValue < 0 || pwmValue > 100) {
                return crow::response(400, "Value must be between 0 and 100.");
            }
            // 74 - 84 - 94
            int dutyCycle = pwmValue / 5 + 74;

            // Set the PWM duty cycle on the GPIO pin
            gpioPWM(SERVO_PIN, dutyCycle);

            // Update the global current PWM value
            {
                std::lock_guard<std::mutex> lock(servoMutex);
                servoPercentage = pwmValue;
            }

            std::ostringstream msg;
            msg << "PWM set to " << pwmValue << "% (Duty Cycle: " << dutyCycle << ").";
            return crow::response(200, msg.str());
        } catch (const std::exception& e) {
            return crow::response(500, std::string("Internal Server Error: ") + e.what());
        }
    });

    CROW_ROUTE(app, "/distance").methods(crow::HTTPMethod::GET)([]() {
        updateDistance();
        {
            std::lock_guard<std::mutex> lock(ultrasonicMutex);
            crow::json::wvalue response;
            response["value"] = currentDistance;
            return crow::response(200, response);
        }
    });

    CROW_ROUTE(app, "/temparature").methods(crow::HTTPMethod::GET)([]() {
        std::lock_guard<std::mutex> lock(ultrasonicMutex);
        crow::json::wvalue response;
        response["value"] = currentDistance;
        return crow::response(200, response);
    });

    // GET route for /engine to get the current PWM value
    CROW_ROUTE(app, "/engine").methods(crow::HTTPMethod::GET)([]() {
        std::lock_guard<std::mutex> lock(engineMutex); // Ensure thread-safe access
        crow::json::wvalue response;
        response["value"] = enginePercentage;
        return crow::response(200, response);
    });

    CROW_ROUTE(app, "/servo").methods(crow::HTTPMethod::GET)([]() {
        std::lock_guard<std::mutex> lock(servoMutex); // Ensure thread-safe access
        crow::json::wvalue response;
        response["value"] = servoPercentage;
        return crow::response(200, response);
    });

    std::cout << "Server is running on http://192.168.137.13:18080" << std::endl;

    // Run the server on port 18080
    app.port(18080).multithreaded().run();

    // Cleanup pigpio on exit
    gpioPWM(SERVO_PIN, 84);
    gpioPWM(ENGINE_PIN, 80);
    gpioTerminate();
    return 0;
}

