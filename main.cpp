#include <iostream>
#include <stdexcept>
#include "mpu.hpp"

static constexpr float G_FORCE = 9.80665f;

int main()
{
    try
    {
        sensor::imu::Mpu9250 Mpu9250;
        sensor::imu::mpu_data data;

        data = Mpu9250.GetAccelReading();

        std::cout << "\nwartosc x: " << data[sensor::imu::X].raw;
        std::cout << "\nwartosc y: " << data[sensor::imu::Y].raw;
        std::cout << "\nwartosc z: " << data[sensor::imu::Z].raw;

        // data.x = data.x * (2.0f / 32767.5f) * G_FORCE;
        // std::cout << "\nwartosc x przeliczona: " << data.x;

    }

    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    std::cout << "\n\n\n\n";
}