cmake_minimum_required(VERSION 3.5)
project(myschedule)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 启用Qt的自动工具
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 查找Qt5
find_package(Qt5 REQUIRED COMPONENTS Widgets)

# 包含目录
include_directories(include)

# 源文件
set(SOURCES
    src/main.cpp
    src/CommandLineInterface.cpp
    src/AddTaskDialog.cpp
    src/TaskListDialog.cpp
    src/EditTaskDialog.cpp
    src/TaskManager.cpp
    src/User.cpp
    src/Task.cpp
    src/Scheduler.cpp
    src/Utils.cpp
)

# 头文件
set(HEADERS
    include/CommandLineInterface.h
    include/AddTaskDialog.h
    include/TaskListDialog.h
    include/EditTaskDialog.h
    include/TaskManager.h
    include/User.h
    include/Task.h
    include/Scheduler.h
    include/Utils.h
)

# 创建可执行文件
add_executable(myschedule ${SOURCES} ${HEADERS})

# 链接Qt库
target_link_libraries(myschedule Qt5::Widgets)

# 如果需要OpenSSL（用于User类的密码哈希）
find_package(OpenSSL REQUIRED)
target_link_libraries(myschedule ${OPENSSL_LIBRARIES})
target_include_directories(myschedule PRIVATE ${OPENSSL_INCLUDE_DIR})