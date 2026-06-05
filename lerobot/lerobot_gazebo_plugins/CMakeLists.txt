cmake_minimum_required(VERSION 3.8)
project(lerobot_gazebo_plugins)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)
find_package(pluginlib REQUIRED)
find_package(hardware_interface REQUIRED)
find_package(controller_manager REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(trajectory_msgs REQUIRED)
find_package(control_msgs REQUIRED)
find_package(gz_sim_vendor REQUIRED)
find_package(gz-sim REQUIRED)

find_package(gz_plugin_vendor REQUIRED)
find_package(gz-plugin REQUIRED)

find_package(gz_common_vendor REQUIRED)
find_package(gz-common REQUIRED)

find_package(gz_ros2_control REQUIRED)

include_directories(include)

add_library(lerobot_hardware_interface SHARED
  src/lerobot_hardware_interface.cpp
)

ament_target_dependencies(lerobot_hardware_interface
  rclcpp
  rclcpp_lifecycle
  pluginlib
  hardware_interface
  controller_manager
  sensor_msgs
  std_msgs
  trajectory_msgs
  control_msgs
  gz_ros2_control
)

target_include_directories(lerobot_hardware_interface PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

add_library(lerobot_moveit_adapter SHARED
  src/lerobot_moveit_adapter.cpp
)

ament_target_dependencies(lerobot_moveit_adapter
  rclcpp
  rclcpp_lifecycle
  pluginlib
  hardware_interface
  controller_manager
  sensor_msgs
  std_msgs
  trajectory_msgs
  control_msgs
  gz_ros2_control
)

target_link_libraries(lerobot_hardware_interface
  gz-sim::gz-sim
  gz-plugin::gz-plugin
  gz-common::gz-common
)

target_link_libraries(lerobot_moveit_adapter
  gz-sim::gz-sim
  gz-plugin::gz-plugin
  gz-common::gz-common
)

target_include_directories(lerobot_moveit_adapter PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

pluginlib_export_plugin_description_file(
  gz_ros2_control
  urdf/lerobot_hardware_interface_plugin.xml
)

install(
  DIRECTORY include/
  DESTINATION include
)

install(
  TARGETS
    lerobot_hardware_interface
    lerobot_moveit_adapter
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(
  DIRECTORY
    config
    launch
    urdf
  DESTINATION share/${PROJECT_NAME}
)



ament_export_include_directories(include)
ament_export_libraries(
  lerobot_hardware_interface
  lerobot_moveit_adapter
)
ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)

ament_package()