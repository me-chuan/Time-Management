# 设置最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称和版本
project(ScheduleManagement VERSION 1.0)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含头文件目录
include_directories(include)

# 源文件列表
set(SOURCES
    src/main.cpp
    src/Task.cpp
    src/User.cpp
    src/TaskManager.cpp
    src/Scheduler.cpp
    src/CommandLineInterface.cpp
    src/Utils.cpp
)

# 添加可执行文件
add_executable(myschedule ${SOURCES})

# 链接线程库
find_package(Threads REQUIRED)
target_link_libraries(myschedule Threads::Threads)

# 链接 OpenSSL 库
find_package(OpenSSL REQUIRED)
target_link_libraries(myschedule OpenSSL::SSL OpenSSL::Crypto)