cmake_minimum_required(VERSION 3.5)
project(serial_port_node)

# 设置C++标准
set(CMAKE_CXX_STANDARD 14)

# 查找依赖项
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(serial REQUIRED)

# 添加可执行文件
add_executable(serial_port_node src/serial_port_node.cpp)

# 指定依赖项包含目录
target_include_directories(serial_port_node PRIVATE ${serial_INCLUDE_DIRS})

# 指定链接的依赖项
target_link_libraries(serial_port_node ${serial_LIBRARIES})

# 添加依赖项
ament_target_dependencies(serial_port_node
  rclcpp
  std_msgs
  serial)

# 添加安装目标
install(
  TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

# 导出ROS2软件包元数据
ament_package()
