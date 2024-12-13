#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libevent::core" for configuration "Debug"
set_property(TARGET libevent::core APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(libevent::core PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libevent_cored.a"
  )

list(APPEND _cmake_import_check_targets libevent::core )
list(APPEND _cmake_import_check_files_for_libevent::core "${_IMPORT_PREFIX}/lib/libevent_cored.a" )

# Import target "libevent::extra" for configuration "Debug"
set_property(TARGET libevent::extra APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(libevent::extra PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libevent_extrad.a"
  )

list(APPEND _cmake_import_check_targets libevent::extra )
list(APPEND _cmake_import_check_files_for_libevent::extra "${_IMPORT_PREFIX}/lib/libevent_extrad.a" )

# Import target "libevent::openssl" for configuration "Debug"
set_property(TARGET libevent::openssl APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(libevent::openssl PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libevent_openssld.a"
  )

list(APPEND _cmake_import_check_targets libevent::openssl )
list(APPEND _cmake_import_check_files_for_libevent::openssl "${_IMPORT_PREFIX}/lib/libevent_openssld.a" )

# Import target "libevent::pthreads" for configuration "Debug"
set_property(TARGET libevent::pthreads APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(libevent::pthreads PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libevent_pthreadsd.a"
  )

list(APPEND _cmake_import_check_targets libevent::pthreads )
list(APPEND _cmake_import_check_files_for_libevent::pthreads "${_IMPORT_PREFIX}/lib/libevent_pthreadsd.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
