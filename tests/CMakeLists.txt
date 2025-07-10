cmake_minimum_required(VERSION 3.10)
project(TestProject)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 包含头文件目录
include_directories(../include)

# 源文件列表
set(SOURCES
    test_main.cpp
    ../src/Task.cpp
    ../src/User.cpp
)

# 查找 OpenSSL 库
find_package(OpenSSL REQUIRED)

# 生成可执行文件
add_executable(test_project ${SOURCES})

# 链接 OpenSSL 库
target_link_libraries(test_project OpenSSL::SSL OpenSSL::Crypto)