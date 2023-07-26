cmake_minimum_required(VERSION 3.8)
project(imu)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

add_executable(mpu9250 
src/mpu9250.cpp
src/mpu9250_handlers.cpp)

target_include_directories(mpu9250 PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/imu>
$<INSTALL_INTERFACE:include>)  

install(TARGETS mpu9250
  DESTINATION lib/${PROJECT_NAME})

target_compile_features(mpu9250 PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(mpu9250 rclcpp std_msgs sensor_msgs)
  

ament_package()
