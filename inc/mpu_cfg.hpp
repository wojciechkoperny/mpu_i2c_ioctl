#ifndef MPU_CFG_HPP_INCLUDE
#define MPU_CFG_HPP_INCLUDE
#include <iostream>

namespace sensor::imu::configs
{
    const std::string I2C_PI_ADAPTER_ADDRESS{"/dev/i2c-1"};
    constexpr int I2C_MPU_DEVICE{0x68U};
    constexpr int PWR_MGMT_1_RESET_VAL{0x0U};
} // namespace sensor::imu

#endif /* MPU_CFG_HPP_INCLUDE */
