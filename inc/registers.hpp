#ifndef REGISTERS_HPP_INCLUDE
#define REGISTERS_HPP_INCLUDE

#include <cstdint>

namespace sensor::imu::registers
{
    // register address from https://invensense.tdk.com/wp-content/uploads/2015/02/RM-MPU-9250A-00-v1.6.pdf
    constexpr uint8_t PWR_MGMT_1{0x6B};
    constexpr uint8_t ACCEL_XOUT_H{0x3B};
    constexpr uint8_t ACCEL_XOUT_L{0x3C};
    constexpr uint8_t ACCEL_YOUT_H{0x3D};
    constexpr uint8_t ACCEL_YOUT_L{0x3E};
    constexpr uint8_t ACCEL_ZOUT_H{0x3F};
    constexpr uint8_t ACCEL_ZOUT_L{0x40};
    constexpr uint8_t TEMP_OUT_H{0x41};
    constexpr uint8_t TEMP_OUT_L{0x42};
    constexpr uint8_t GYRO_XOUT_H{0x43};
    constexpr uint8_t GYRO_XOUT_L{0x44};
    constexpr uint8_t GYRO_YOUT_H{0x45};
    constexpr uint8_t GYRO_YOUT_L{0x46};
    constexpr uint8_t GYRO_ZOUT_H{0x47};
    constexpr uint8_t GYRO_ZOUT_L{0x48};
    constexpr uint8_t HXL{0x03};
    constexpr uint8_t HXH{0x04};
    constexpr uint8_t HYL{0x05};
    constexpr uint8_t HYH{0x06};
    constexpr uint8_t HZL{0x07};
    constexpr uint8_t HZH{0x08};

} // namespace sensor::imu

#endif /* REGISTERS_HPP_INCLUDE */
