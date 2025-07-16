# Schedule Management System

## 项目简介
Schedule Management System 是一个基于 Qt 和 C++ 的任务管理系统，旨在帮助用户高效地管理日程和任务。项目支持图形化界面和命令行交互模式，提供了用户注册、登录、任务管理等功能。

## 功能列表
- **用户管理**：支持用户注册、登录和删除。
- **任务管理**：
  - 添加任务
  - 编辑任务
  - 完成任务
  - 显示任务列表
- **提醒功能**：通过 Scheduler 提供任务提醒功能。
- **多语言支持**：支持中文显示。

## 项目结构
```
FINAL/
├── CMakeLists.txt          # CMake 配置文件
├── audio/                  # 音频相关资源
├── build/                  # 构建文件夹
├── data/                   # 数据文件夹
├── docs/                   # 文档文件夹
├── include/                # 头文件
├── src/                    # 源代码
│   ├── main.cpp            # 主程序入口
│   ├── TaskManager.cpp     # 任务管理逻辑
│   ├── Scheduler.cpp       # 任务提醒逻辑
│   ├── CommandLineInterface.cpp # 命令行交互逻辑
│   ├── EditTaskDialog.cpp  # 编辑任务的图形化界面
│   └── Task.cpp            # 任务类定义
├── tests/                  # 测试文件夹
└── README.md               # 项目说明文件
```

## 环境要求
- **操作系统**：Linux
- **编译器**：支持 C++17 的编译器
- **依赖**：
  - Qt 5 或更高版本
  - CMake 3.22 或更高版本

## 编译与运行
1. **克隆项目**：
   ```bash
   git clone https://github.com/me-chuan/Time-Management.git
   cd Time-Management/FINAL
   ```

2. **构建项目**：
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

3. **运行程序**：
   ```bash
   ./myschedule
   ```

## 使用说明
- **命令行模式**：
  - 启动后，用户可以选择注册、登录或删除用户。
  - 登录成功后，进入任务管理模式。
- **图形化界面**：
  - 提供任务添加、编辑和显示功能。

## 贡献指南
欢迎对项目进行贡献！请提交 Pull Request 或报告问题。
