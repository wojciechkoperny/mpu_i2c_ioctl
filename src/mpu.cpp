#include <iostream>
#include <stdexcept>
#include "mpu.hpp"
#include "mpu_cfg.hpp"
#include "registers.hpp"

// #include <stdio.h>
// #include <stdlib.h>
// #include <errno.h>
// #include <string.h>
#include <cerrno>
#include <cstring>
#include <clocale>

#include <unistd.h>        //Needed for I2C port
#include <fcntl.h>         //Needed for I2C port
#include <sys/ioctl.h>     //Needed for I2C port
#include <linux/i2c-dev.h> //Needed for I2C port
#include <linux/i2c.h>

namespace sensor::imu
{

    Mpu9250::Mpu9250()
    {
        int err;

        // open i2c
        deviceID = open(sensor::imu::configs::I2C_PI_ADAPTER_ADDRESS.c_str(), O_RDWR);
        if (deviceID < 0)
        {
            err = errno;
            throw std::runtime_error(std::string("Error while trying to open i2c: ") + std::strerror(err));
        }

        // setup mpu address
        if (ioctl(deviceID, I2C_SLAVE, sensor::imu::configs::I2C_MPU_DEVICE))
        {
            err = errno;
            throw std::runtime_error(std::string("Error while trying to set up i2c: ") + std::strerror(err));
        }

        // reset power register
        (void)i2c_writeRegister(sensor::imu::registers::PWR_MGMT_1, 0x0);
    }
    Mpu9250::~Mpu9250()
    {
        close(deviceID);
    }

    void Mpu9250::i2c_writeRegister(uint8_t const command, uint8_t const value)
    {
        uint8_t data[2] = {command, value};
        int err;

        if (write(deviceID, data, 2U) != 2U)
        {
            err = errno;
            throw std::runtime_error(std::string("Error while trying to send data to i2c: ") + std::strerror(err));
        }
    }

    uint8_t Mpu9250::i2c_readRegister(uint8_t const command)
    {
        union i2c_smbus_data data;
        data.byte = 0;
        int err;

        struct i2c_smbus_ioctl_data args;

        args.read_write = I2C_SMBUS_READ;
        args.command = command;
        args.size = I2C_SMBUS_BYTE_DATA;
        args.data = &data;

        err = ioctl(deviceID, I2C_SMBUS, &args);
        if (err == -1)
        {
            throw std::runtime_error(std::string("Error while trying to send data to i2c: ") + std::strerror(err));
            return 0;
        }
        else
        {
            return 0xFF & data.byte;
        }
    }

    mpu_data Mpu9250::GetAccelReading()
    {
        mpu_data data;

        data.x = i2c_readRegister(sensor::imu::registers::ACCEL_XOUT_H);
        data.x = data.x << 8;
        data.x += i2c_readRegister(sensor::imu::registers::ACCEL_XOUT_L);
        if (data.x >= 0x8000)
        {
            data.x = -(65536 - data.x);
        }
        data.y = 2;
        data.z = 3;
        return data;
    }

} // namespace sensor::imu
