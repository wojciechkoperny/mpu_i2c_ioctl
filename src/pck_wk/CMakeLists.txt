cmake_minimum_required(VERSION 3.8)
project(pck_wk)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

add_executable(my_node 
src/my_node.cpp
src/mpu.cpp)

target_include_directories(my_node PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:include>)  

install(TARGETS my_node
    DESTINATION lib/${PROJECT_NAME})

target_compile_features(my_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(my_node rclcpp std_msgs sensor_msgs)
  

ament_package()
