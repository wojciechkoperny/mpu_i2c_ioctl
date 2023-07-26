#include <iostream>
#include <stdexcept>
#include "mpu.hpp"
#include "mpu_cfg.hpp"
#include "registers.hpp"
#include "mpu_priv.hpp"

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
        i2c_writeRegister(sensor::imu::registers::PWR_MGMT_1, 0x0);

        changeGyroDLPF(MPU9250_DLPF_6);
        changeAccelDLPF(MPU9250_DLPF_6);
        changeSampleRateDivider(5);
    }
    Mpu9250::~Mpu9250()
    {
        close(deviceID);
    }

    void Mpu9250::changeGyroDLPF(MPU9250_DLPF dlpf)
    {
        // fchoice set to use DLPF
        uint8_t regVal = i2c_readRegister(sensor::imu::registers::GYRO_CONFIG);
        regVal &= 0xFC;
        i2c_writeRegister(sensor::imu::registers::GYRO_CONFIG, regVal);

        // enable requested DLPF
        regVal = i2c_readRegister(sensor::imu::registers::CONFIG);
        regVal &= 0xF8;
        regVal |= dlpf;
        i2c_writeRegister(sensor::imu::registers::CONFIG, regVal);
    }

    void Mpu9250::changeAccelDLPF(MPU9250_DLPF dlpf)
    {
        uint8_t regVal = i2c_readRegister(sensor::imu::registers::ACCEL_CONFIG_2);
        // fchoice set to use DLPF
        regVal &= ~8;

        // enable requested DLPF
        regVal &= 0xF8;
        regVal |= dlpf;
        i2c_writeRegister(sensor::imu::registers::ACCEL_CONFIG_2, regVal);
    }

    void Mpu9250::changeSampleRateDivider(uint8_t divider)
    {
        i2c_writeRegister(sensor::imu::registers::SMPLRT_DIV, divider);
    }

    bool Mpu9250::SelfTestProcedure()
    {
        return true;
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
        int temp_data_raw[3]={0};

        for (int i = 0; i < 3; i++)
        {
            temp_data_raw[i] = i2c_readRegister(sensor::imu::registers_array[sensor::imu::ACCEL_REG][i][sensor::imu::HIGH_BYTE_REG]);
            temp_data_raw[i] = temp_data_raw[i] << 8;
            temp_data_raw[i] += i2c_readRegister(sensor::imu::registers_array[sensor::imu::ACCEL_REG][i][sensor::imu::LOW_BYTE_REG]);
            if (temp_data_raw[i] >= 0x8000)
            {
                data[i].raw = -(0x10000 - temp_data_raw[i]);
            }
            else
            {
                data[i].raw = temp_data_raw[i];
            }
            data[i].scaled = data[i].raw * (2.0f / 32767.5f) * sensor::imu::configs::G_FORCE;
            data[i].unit = "m/s^2";
        }
        return data;
    }

    mpu_data Mpu9250::GetGyroReading()
    {
        mpu_data data;
        int temp_data_raw[3] = {0};

        for (int i = 0; i < 3; i++)
        {
            temp_data_raw[i] = i2c_readRegister(sensor::imu::registers_array[sensor::imu::GYRO_REG][i][sensor::imu::HIGH_BYTE_REG]);
            temp_data_raw[i] = temp_data_raw[i] << 8;
            temp_data_raw[i] += i2c_readRegister(sensor::imu::registers_array[sensor::imu::GYRO_REG][i][sensor::imu::LOW_BYTE_REG]);
            if (temp_data_raw[i] >= 0x8000)
            {
                data[i].raw = -(0x10000 - temp_data_raw[i]);
            }
            else
            {
                data[i].raw = temp_data_raw[i];
            }
            data[i].scaled = (data[i].raw / 131.0f) * 0.01745f;
            data[i].unit = "rad/sec";
        }
        return data;
    }

    mpu_data Mpu9250::GetMagReading()
    {
        mpu_data data;
        int temp_data_raw[3] = {0};

        for (int i = 0; i < 3; i++)
        {
            temp_data_raw[i] = i2c_readRegister(sensor::imu::registers_array[sensor::imu::MAG_REG][i][sensor::imu::HIGH_BYTE_REG]);
            temp_data_raw[i] = temp_data_raw[i] << 8;
            temp_data_raw[i] += i2c_readRegister(sensor::imu::registers_array[sensor::imu::MAG_REG][i][sensor::imu::LOW_BYTE_REG]);
            if (temp_data_raw[i] >= 0x8000)
            {
                data[i].raw = -(0x10000 - temp_data_raw[i]);
            }
            else
            {
                data[i].raw = temp_data_raw[i];
            }
            data[i].scaled = data[i].raw;
            data[i].unit = "m/s^2";
        }
        return data;
    }

    double Mpu9250::GetTempReading()
    {
        double data;
        int raw;

        raw = i2c_readRegister(sensor::imu::temp_register[sensor::imu::HIGH_BYTE_REG]);
        raw = raw << 8;
        raw += i2c_readRegister(sensor::imu::temp_register[sensor::imu::LOW_BYTE_REG]);
        data = (raw - sensor::imu::configs::ROOMTEMP_OFFSET) / sensor::imu::configs::TEMP_SENSITIVITY + 21.0;

        return data;
    }
} // namespace sensor::imu
