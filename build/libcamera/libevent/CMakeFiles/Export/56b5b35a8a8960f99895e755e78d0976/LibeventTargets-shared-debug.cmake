#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libevent::core" for configuration "Debug"
set_property(TARGET libevent::core APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(libevent::core PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libevent_core-2.2d.so.1.0.0"
  IMPORTED_SONAME_DEBUG "libevent_core-2.2d.so.1"
  )

list(APPEND _cmake_import_check_targets libevent::core )
list(APPEND _cmake_import_check_files_for_libevent::core "${_IMPORT_PREFIX}/lib/libevent_core-2.2d.so.1.0.0" )

# Import target "libevent::extra" for configuration "Debug"
set_property(TARGET libevent::extra APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(libevent::extra PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libevent_extra-2.2d.so.1.0.0"
  IMPORTED_SONAME_DEBUG "libevent_extra-2.2d.so.1"
  )

list(APPEND _cmake_import_check_targets libevent::extra )
list(APPEND _cmake_import_check_files_for_libevent::extra "${_IMPORT_PREFIX}/lib/libevent_extra-2.2d.so.1.0.0" )

# Import target "libevent::openssl" for configuration "Debug"
set_property(TARGET libevent::openssl APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(libevent::openssl PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libevent_openssl-2.2d.so.1.0.0"
  IMPORTED_SONAME_DEBUG "libevent_openssl-2.2d.so.1"
  )

list(APPEND _cmake_import_check_targets libevent::openssl )
list(APPEND _cmake_import_check_files_for_libevent::openssl "${_IMPORT_PREFIX}/lib/libevent_openssl-2.2d.so.1.0.0" )

# Import target "libevent::pthreads" for configuration "Debug"
set_property(TARGET libevent::pthreads APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(libevent::pthreads PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libevent_pthreads-2.2d.so.1.0.0"
  IMPORTED_SONAME_DEBUG "libevent_pthreads-2.2d.so.1"
  )

list(APPEND _cmake_import_check_targets libevent::pthreads )
list(APPEND _cmake_import_check_files_for_libevent::pthreads "${_IMPORT_PREFIX}/lib/libevent_pthreads-2.2d.so.1.0.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
