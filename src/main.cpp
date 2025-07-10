#include "TaskManager.h"
#include "Scheduler.h"
#include "CommandLineInterface.h"
#include <iostream>

int main() {
    // 创建 TaskManager 实例
    TaskManager taskManager;

    // 加载任务数据
    taskManager.loadFromFile("../data/tasks.txt");

    // 创建 Scheduler 实例
    Scheduler scheduler(taskManager);

    // 创建 CommandLineInterface 实例
    CommandLineInterface cli(taskManager, scheduler);

    // 显示欢迎信息
    std::cout << "Welcome to the Schedule Management System!" << std::endl;
    std::cout << "Type 'help' for available commands." << std::endl;

    // 进入命令行交互模式
    cli.runShellMode();

    // 保存任务数据
    taskManager.saveToFile("../data/tasks.txt");

    return 0;
}
