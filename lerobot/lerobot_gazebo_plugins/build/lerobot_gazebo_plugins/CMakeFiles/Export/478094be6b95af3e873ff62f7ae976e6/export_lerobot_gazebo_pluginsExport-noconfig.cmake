#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "lerobot_gazebo_plugins::lerobot_hardware_interface" for configuration ""
set_property(TARGET lerobot_gazebo_plugins::lerobot_hardware_interface APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(lerobot_gazebo_plugins::lerobot_hardware_interface PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/liblerobot_hardware_interface.so"
  IMPORTED_SONAME_NOCONFIG "liblerobot_hardware_interface.so"
  )

list(APPEND _cmake_import_check_targets lerobot_gazebo_plugins::lerobot_hardware_interface )
list(APPEND _cmake_import_check_files_for_lerobot_gazebo_plugins::lerobot_hardware_interface "${_IMPORT_PREFIX}/lib/liblerobot_hardware_interface.so" )

# Import target "lerobot_gazebo_plugins::lerobot_moveit_adapter" for configuration ""
set_property(TARGET lerobot_gazebo_plugins::lerobot_moveit_adapter APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(lerobot_gazebo_plugins::lerobot_moveit_adapter PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/liblerobot_moveit_adapter.so"
  IMPORTED_SONAME_NOCONFIG "liblerobot_moveit_adapter.so"
  )

list(APPEND _cmake_import_check_targets lerobot_gazebo_plugins::lerobot_moveit_adapter )
list(APPEND _cmake_import_check_files_for_lerobot_gazebo_plugins::lerobot_moveit_adapter "${_IMPORT_PREFIX}/lib/liblerobot_moveit_adapter.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
