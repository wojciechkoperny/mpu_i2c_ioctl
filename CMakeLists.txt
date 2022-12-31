cmake_minimum_required(VERSION 3.10)
project(test_proj VERSION 1.0)

SET(CMAKE_MAKE_PROGRAM make)

#add_library(libpthread STATIC IMPORTED)

add_executable(test_proj1   src/mpu.cpp
                            main.cpp)
                            
target_include_directories(test_proj1 PUBLIC inc)
target_link_libraries(test_proj1 pthread)