cmake_minimum_required(VERSION 3.5)
project(vision_dnn)

# 设置C++标准
set(CMAKE_CXX_STANDARD 14)

# 查找依赖项
find_package(ament_cmake REQUIRED)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

# 导出ROS2软件包元数据
ament_package()
