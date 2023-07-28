#include <iostream>
#include <string>
#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "serial/serial.h"

class SerialPortNode : public rclcpp::Node
{
    public:
    SerialPortNode(const std::string& port): Node("serial_port_node")
    {
        // 初始化串口
        serial::Timeout timeout = serial::Timeout::simpleTimeout(1000);
        serial_port_.setPort(port);
        serial_port_.setBaudrate(115200);
        serial_port_.setTimeout(timeout);

        // 创建订阅者和发布者
        subscriber_ = this->create_subscription<std_msgs::msg::String>("serial_input", 10, [this](const std_msgs::msg::String::SharedPtr msg) {
            serial_port_.write(msg->data);
        });

        publisher_ = this->create_publisher<std_msgs::msg::String>("serial_output", 10);

        // 打开串口
        try {
            serial_port_.open();
        } catch (serial::IOException& e) {
            RCLCPP_ERROR(this->get_logger(), "无法打开串口");
            RCLCPP_ERROR(this->get_logger(), e.what());
        }

        // 启动串口数据接收线程
        receive_thread_ = std::thread([this]() {
            while (rclcpp::ok()) {
                if (serial_port_.isOpen()) {
                    size_t bytes_available = serial_port_.available();
                    if (bytes_available > 0) {
                        std::string data = serial_port_.read(bytes_available);
                        std_msgs::msg::String msg;
                        msg.data = data;
                        publisher_->publish(msg);
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });
    }

    ~SerialPortNode()
    {
        if (serial_port_.isOpen()) {
            serial_port_.close();
        }

        if (receive_thread_.joinable()) {
            receive_thread_.join();
        }
    }

    private:
    serial::Serial serial_port_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    std::thread receive_thread_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    std::string port = "";
    if (argc > 1) {
            port = argv[1];
        }
    auto node = std::make_shared<SerialPortNode>(port);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}