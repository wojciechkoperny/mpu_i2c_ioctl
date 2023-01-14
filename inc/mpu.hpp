#ifndef MPU_HPP_INCLUDE
#define MPU_HPP_INCLUDE

#include <cstdint>
#include <iostream>
#include <array>

namespace sensor::imu
{
    constexpr uint8_t X{0};
    constexpr uint8_t Y{1};
    constexpr uint8_t Z{2};

    typedef struct
    {
        int16_t raw;
        double scaled;
        std::string unit;
    } record_data;

    typedef std::array<record_data, 3> mpu_data;

    class Mpu9250
    {
    public:
        Mpu9250();
        ~Mpu9250();

        mpu_data GetAccelReading();
        mpu_data GetGyroReading();
        mpu_data GetMagReading();
        double GetTempReading();

    private:
        void i2c_writeRegister(uint8_t const command, uint8_t const value);
        uint8_t i2c_readRegister(uint8_t const command);

        int deviceID;
    };

} // namespace sensor::imu

#endif /* MPU_HPP_INCLUDE */
