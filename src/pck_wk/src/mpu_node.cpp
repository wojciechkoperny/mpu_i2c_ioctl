#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <memory>
#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "sensor_msgs/msg/magnetic_field.hpp"
#include "mpu.hpp"

static constexpr float G_FORCE = 9.80665f;

class ImuPublisher : public rclcpp::Node
{
public:
    ImuPublisher() : Node("ImuPublisher")
    {
        mPublisherImu = this->create_publisher<sensor_msgs::msg::Imu>("/imu/data_raw", 10);
        mPublisherMag = this->create_publisher<sensor_msgs::msg::MagneticField>("/imu/mag", 10);
        mTimer = this->create_wall_timer(std::chrono::duration<double, std::milli>(100), std::bind(&ImuPublisher::timer_callback, this));
    }

private:
    void timer_callback()
    {
        auto messageImu = sensor_msgs::msg::Imu();
        sensor::imu::mpu_data data;

        messageImu.header.frame_id = "imu";
        messageImu.header.stamp = rclcpp::Clock().now();

        data = Mpu9250.GetAccelReading();

        messageImu.linear_acceleration.x = data[sensor::imu::X].scaled;
        messageImu.linear_acceleration.y = data[sensor::imu::Y].scaled;
        messageImu.linear_acceleration.z = data[sensor::imu::Z].scaled;

        data = Mpu9250.GetGyroReading();
        messageImu.angular_velocity.x = data[sensor::imu::X].scaled;
        messageImu.angular_velocity.y = data[sensor::imu::Y].scaled;
        messageImu.angular_velocity.z = data[sensor::imu::Z].scaled;

        mPublisherImu->publish(messageImu);
    }

    sensor::imu::Mpu9250 Mpu9250;

    rclcpp::TimerBase::SharedPtr mTimer;
    rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr mPublisherImu;
    rclcpp::Publisher<sensor_msgs::msg::MagneticField>::SharedPtr mPublisherMag;
};

int main(int argc, char **argv)
{

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImuPublisher>());
    rclcpp::shutdown();
    return 0;
}
