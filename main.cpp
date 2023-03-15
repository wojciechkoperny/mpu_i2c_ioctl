#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <iomanip>
#include "mpu.hpp"

static constexpr float G_FORCE = 9.80665f;

int main()
{
    try
    {
        sensor::imu::Mpu9250 Mpu9250;
        sensor::imu::mpu_data data;
        sensor::imu::mpu_data dataAcc;
        sensor::imu::mpu_data dataGyr;
        double temp;

        while (1)
        {

            usleep(500000);

            dataAcc = Mpu9250.GetAccelReading();
            dataGyr = Mpu9250.GetGyroReading();

            std::cout << std::fixed;
            std::cout << std::setprecision(3);

            std::cout << "\nwartosc x: " << dataAcc[sensor::imu::X].scaled << dataAcc[sensor::imu::X].unit << "\t"
                      << "\t" << dataGyr[sensor::imu::X].scaled << dataGyr[sensor::imu::X].unit;
            std::cout << "\nwartosc y: " << dataAcc[sensor::imu::Y].scaled << dataAcc[sensor::imu::Y].unit << "\t"
                      << "\t" << dataGyr[sensor::imu::Y].scaled << dataGyr[sensor::imu::Y].unit;
            std::cout << "\nwartosc z: " << dataAcc[sensor::imu::Z].scaled << dataAcc[sensor::imu::Z].unit << "\t"
                      << "\t" << dataGyr[sensor::imu::Z].scaled << dataGyr[sensor::imu::Z].unit;
            std::cout << "\n--------------------------";

            // std::cout << "\nwartosc x: " << dataGyr[sensor::imu::X].scaled << "\t" << dataGyr[sensor::imu::X].unit;
            // std::cout << "\nwartosc y: " << dataGyr[sensor::imu::Y].scaled << "\t" << dataGyr[sensor::imu::Y].unit;
            // std::cout << "\nwartosc z: " << dataGyr[sensor::imu::Z].scaled << "\t" << dataGyr[sensor::imu::Z].unit;
            // std::cout << "\n--------------------------";

            // data = Mpu9250.GetMagReading();
            // std::cout << "\nmag x: " << data[sensor::imu::X].scaled << "\t" << data[sensor::imu::X].unit;
            // std::cout << "\nmag y: " << data[sensor::imu::Y].scaled << "\t" << data[sensor::imu::Y].unit;
            // std::cout << "\nmag z: " << data[sensor::imu::Z].scaled << "\t" << data[sensor::imu::Z].unit;
            // std::cout << "\n--------------------------";

            // temp = Mpu9250.GetTempReading();
            // std::cout << "\ntemperatura: " << temp << " Celsius";
            // std::cout << "\n--------------------------";
        }
    }

    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    std::cout << "\n\n\n\n";
}