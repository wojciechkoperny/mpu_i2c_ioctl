#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include "mpu.hpp"

static constexpr float G_FORCE = 9.80665f;

int main()
{
    try
    {
        sensor::imu::Mpu9250 Mpu9250;
        sensor::imu::mpu_data data;
        double temp;

        while (1)
        {

            usleep(500000);

            data = Mpu9250.GetAccelReading();

            std::cout << "\nwartosc x: " << data[sensor::imu::X].scaled << data[sensor::imu::X].unit;
            std::cout << "\nwartosc y: " << data[sensor::imu::Y].scaled << data[sensor::imu::Y].unit;
            std::cout << "\nwartosc z: " << data[sensor::imu::Z].scaled << data[sensor::imu::Z].unit;
            std::cout << "\n--------------------------";

            data = Mpu9250.GetGyroReading();
            std::cout << "\nwartosc x: " << data[sensor::imu::X].scaled << "\t" << data[sensor::imu::X].unit;
            std::cout << "\nwartosc y: " << data[sensor::imu::Y].scaled << "\t" << data[sensor::imu::Y].unit;
            std::cout << "\nwartosc z: " << data[sensor::imu::Z].scaled << "\t" << data[sensor::imu::Z].unit;
            std::cout << "\n--------------------------";

            data = Mpu9250.GetMagReading();
            std::cout << "\nmag x: " << data[sensor::imu::X].scaled << "\t" << data[sensor::imu::X].unit;
            std::cout << "\nmag y: " << data[sensor::imu::Y].scaled << "\t" << data[sensor::imu::Y].unit;
            std::cout << "\nmag z: " << data[sensor::imu::Z].scaled << "\t" << data[sensor::imu::Z].unit;
            std::cout << "\n--------------------------";

            temp = Mpu9250.GetTempReading();
            std::cout << "\ntemperatura: " << temp << " Celsius";
            std::cout << "\n--------------------------";
        }
    }

    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    std::cout << "\n\n\n\n";
}