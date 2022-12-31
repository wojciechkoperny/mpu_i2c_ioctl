#ifndef MPU_HPP_INCLUDE
#define MPU_HPP_INCLUDE

#include <cstdint>
#include <vector>
// #include <memory>

namespace sensor::imu
{
    typedef struct
    {
        int16_t x;
        int16_t y;
        int16_t z;
    } mpu_data;

    class Mpu9250
    {
    public:
        Mpu9250();
        ~Mpu9250();

        mpu_data GetAccelReading();

    private:
        void i2c_writeRegister(uint8_t const command, uint8_t const value);
        uint8_t i2c_readRegister(uint8_t const command);
        
        int deviceID;
    };

} // namespace sensor::imu

#endif /* MPU_HPP_INCLUDE */
