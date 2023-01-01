#ifndef MPU_PRIV_HPP_INCLUDE
#define MPU_PRIV_HPP_INCLUDE

// #include <cstdint>
#include "registers.hpp"

namespace sensor::imu
{
    uint8_t x_acc_register[]{sensor::imu::registers::ACCEL_XOUT_H, sensor::imu::registers::ACCEL_XOUT_L};
    uint8_t y_acc_register[]{sensor::imu::registers::ACCEL_YOUT_H, sensor::imu::registers::ACCEL_YOUT_L};
    uint8_t z_acc_register[]{sensor::imu::registers::ACCEL_ZOUT_H, sensor::imu::registers::ACCEL_ZOUT_L};
    uint8_t* accel_register[]{x_acc_register, y_acc_register, z_acc_register};

    uint8_t x_gyro_register[]{sensor::imu::registers::GYRO_XOUT_H, sensor::imu::registers::GYRO_XOUT_L};
    uint8_t y_gyro_register[]{sensor::imu::registers::GYRO_YOUT_H, sensor::imu::registers::GYRO_YOUT_L};
    uint8_t z_gyro_register[]{sensor::imu::registers::GYRO_ZOUT_H, sensor::imu::registers::GYRO_ZOUT_L};
    uint8_t* gyro_register[]{x_gyro_register, y_gyro_register, z_gyro_register};

    uint8_t temp_register[]{sensor::imu::registers::TEMP_OUT_H, sensor::imu::registers::TEMP_OUT_L};

    uint8_t** registers_array[]{accel_register, gyro_register};

} // namespace sensor::imu

#endif /* MPU_PRIV_HPP_INCLUDE */
