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
    constexpr uint8_t ACCEL_ZOUT_H{0x3F};

} // namespace sensor::imu

#endif /* REGISTERS_HPP_INCLUDE */
