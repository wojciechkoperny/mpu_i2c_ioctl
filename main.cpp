#include <iostream>
#include <stdexcept>
#include "mpu.hpp"

int main()
{
    try
    {
        sensor::imu::Mpu9250 Mpu9250;
        sensor::imu::mpu_data data;

        data = Mpu9250.GetAccelReading();
        // data = sensor::imu::Mpu9250

        std::cout << "\nwartosc x: " << data.x;
        std::cout << "\nwartosc y: " << data.y;
        std::cout << "\nwartosc z: " << data.z;
    }

    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    std::cout << "\n\n\n\n";
}