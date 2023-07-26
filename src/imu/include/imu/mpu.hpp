#ifndef MPU_HPP_INCLUDE
#define MPU_HPP_INCLUDE

#include <cstdint>
#include <iostream>
#include <array>
#include <vector>
#include <numeric>

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

    typedef enum
    {
        MPU9250_DLPF_0 = 0u,
        MPU9250_DLPF_1 = 1u,
        MPU9250_DLPF_2 = 2u,
        MPU9250_DLPF_3 = 3u,
        MPU9250_DLPF_4 = 4u,
        MPU9250_DLPF_5 = 5u,
        MPU9250_DLPF_6 = 6u,
        MPU9250_DLPF_7 = 7u,
    } MPU9250_DLPF;

    typedef std::array<record_data, 3> mpu_data;

    class Mpu9250
    {
    public:
        Mpu9250();
        ~Mpu9250();

        bool SelfTestProcedure();

        mpu_data GetAccelReading();
        mpu_data GetGyroReading();
        mpu_data GetMagReading();
        double GetTempReading();

    private:
        void i2c_writeRegister(uint8_t const command, uint8_t const value);
        uint8_t i2c_readRegister(uint8_t const command);
        void changeAccelDLPF(MPU9250_DLPF dlpf);
        void changeGyroDLPF(MPU9250_DLPF dlpf);
        void changeSampleRateDivider(uint8_t divider);
        template <typename T>
        double getAverage(std::vector<T> const &v);

        int deviceID;
    };

    template <typename T>
    double getAverage(std::vector<T> const &v)
    {
        if (v.empty())
        {
            return 0;
        }

        return std::reduce(v.begin(), v.end(), 0.0) / v.size();
        // /return 0;
    }

} // namespace sensor::imu

#endif /* MPU_HPP_INCLUDE */
