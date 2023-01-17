#ifndef REGISTERS_HPP_INCLUDE
#define REGISTERS_HPP_INCLUDE

#include <cstdint>

namespace sensor::imu::registers
{
    // register address from https://invensense.tdk.com/wp-content/uploads/2015/02/RM-MPU-9250A-00-v1.6.pdf
    constexpr uint8_t SELF_TEST_X_GYRO{0x00};
    constexpr uint8_t SELF_TEST_Y_GYRO{0x01};
    constexpr uint8_t SELF_TEST_Z_GYRO{0x02};
    constexpr uint8_t SELF_TEST_X_ACCEL{0x0D};
    constexpr uint8_t SELF_TEST_Y_ACCEL{0x0E};
    constexpr uint8_t SELF_TEST_Z_ACCEL{0x0F};
    constexpr uint8_t XG_OFFSET_H{0x13};
    constexpr uint8_t XG_OFFSET_L{0x14};
    constexpr uint8_t YG_OFFSET_H{0x15};
    constexpr uint8_t YG_OFFSET_L{0x16};
    constexpr uint8_t ZG_OFFSET_H{0x17};
    constexpr uint8_t ZG_OFFSET_L{0x18};
    constexpr uint8_t SMPLRT_DIV{0x19};
    constexpr uint8_t CONFIG{0x1A};
    constexpr uint8_t GYRO_CONFIG{0x1B};
    constexpr uint8_t ACCEL_CONFIG{0x1C};
    constexpr uint8_t ACCEL_CONFIG_2{0x1D};
    constexpr uint8_t LP_ACCEL_ODR{0x1E};
    constexpr uint8_t WOM_THR{0x1F};
    constexpr uint8_t FIFO_EN{0x23};
    constexpr uint8_t I2C_MST_CTRL{0x24};
    constexpr uint8_t I2C_SLV0_ADDR{0x25};
    constexpr uint8_t I2C_SLV0_REG{0x26};
    constexpr uint8_t I2C_SLV0_CTRL{0x27};
    constexpr uint8_t I2C_SLV1_ADDR{0x28};
    constexpr uint8_t I2C_SLV1_REG{0x29};
    constexpr uint8_t I2C_SLV1_CTRL{0x2A};
    constexpr uint8_t I2C_SLV2_ADDR{0x2B};
    constexpr uint8_t I2C_SLV2_REG{0x2C};
    constexpr uint8_t I2C_SLV2_CTRL{0x2D};
    constexpr uint8_t I2C_SLV3_ADDR{0x2E};
    constexpr uint8_t I2C_SLV3_REG{0x2F};
    constexpr uint8_t I2C_SLV3_CTRL{0x30};
    constexpr uint8_t I2C_SLV4_ADDR{0x31};
    constexpr uint8_t I2C_SLV4_REG{0x32};
    constexpr uint8_t I2C_SLV4_DO{0x33};
    constexpr uint8_t I2C_SLV4_CTRL{0x34};
    constexpr uint8_t I2C_SLV4_DI{0x35};
    constexpr uint8_t I2C_MST_STATUS{0x36};
    constexpr uint8_t INT_PIN_CFG{0x37};
    constexpr uint8_t INT_ENABLE{0x38};
    constexpr uint8_t INT_STATUS{0x3A};

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

    constexpr uint8_t PWR_MGMT_1{0x6B};
} // namespace sensor::imu

#endif /* REGISTERS_HPP_INCLUDE */
