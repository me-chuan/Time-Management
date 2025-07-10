#include "CommandLineInterface.h"
#include <iostream>
#include <sstream>
#include  "Utils.h"

CommandLineInterface::CommandLineInterface(TaskManager& taskManager, Scheduler& scheduler)
    : taskManager(taskManager), scheduler(scheduler) {}

void CommandLineInterface::showHelp() const {
    std::cout << "Available commands:\n"
              << "  addtask <id> <name> <start_time> <reminder_time> [-c <category>] [-p <priority>]\n"
              << "    - id: Task ID (positive integer)\n"
              << "    - name: Task name (non-empty string)\n"
              << "    - start_time: Task start time (format: YYYY-MM-DD_HH:MM)\n"
              << "    - reminder_time: Task reminder time (format: YYYY-MM-DD_HH:MM)\n"
              << "    - -c <category>: Optional task category (default: 未分类)\n"
              << "    - -p <priority>: Optional task priority (default: 中)\n"
              << "  deltask <id>\n"
              << "    - id: Task ID to delete\n"
              << "  showtask\n"
              << "    - Display all tasks\n"
              << "  run\n"
              << "    - Start the reminder thread\n"
              << "  help\n"
              << "    - Show this help message\n"
              << "  exit\n"
              << "    - Exit the program\n";
}

void CommandLineInterface::handleCommand(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << "No command provided. Type 'help' for available commands." << std::endl;
        return;
    }

    const std::string& command = args[0];
    if (command == "addtask" && args.size() >= 5) { // 至少需要5个参数
        try {
            // 检验参数合法性
            int id = std::stoi(args[1]);
            if (id <= 0) {
                throw std::invalid_argument("Task ID must be a positive integer.");
            }

            const std::string& name = args[2];
            if (name.empty()) {
                throw std::invalid_argument("Task name cannot be empty.");
            }

            const std::string& start_time = args[3];
            if (!isValidTimeFormat(start_time)) {
                throw std::invalid_argument("Invalid start time format. Expected format: YYYY-MM-DD_HH:MM.");
            }

            const std::string& reminder_time = args[4];
            if (!isValidTimeFormat(reminder_time)) {
                throw std::invalid_argument("Invalid reminder time format. Expected format: YYYY-MM-DD_HH:MM.");
            }

            // 设置默认值
            std::string category = "未分类";
            std::string priority = "中";

            // 解析可选参数
            for (size_t i = 5; i < args.size(); ++i) {
                if (args[i] == "-c" && i + 1 < args.size()) {
                    category = args[i + 1];
                    ++i; // 跳过参数值
                } else if (args[i] == "-p" && i + 1 < args.size()) {
                    priority = args[i + 1];
                    ++i; // 跳过参数值
                } else {
                    throw std::invalid_argument("Unknown or incomplete parameter: " + args[i]);
                }
            }

            // 添加任务
            taskManager.addTask(Task(id, name, start_time, category, priority, reminder_time));
            taskManager.saveToFile("../data/tasks.txt"); // 保存任务数据到文件
            std::cout << "Task added and saved to file." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error adding task: " << e.what() << std::endl;
        }
    } else if (command == "deltask" && args.size() == 2) {
        int id = std::stoi(args[1]);
        taskManager.deleteTask(id);
        taskManager.saveToFile("../data/tasks.txt"); // 保存任务数据到文件
        std::cout << "Task deleted and saved to file." << std::endl;
    } else if (command == "showtask") {
        auto tasks = taskManager.getAllTasks(); // 获取所有任务
        for (const auto& task : tasks) {
            std::cout << task.toString() << std::endl;
        }
    } else if (command == "run") {
        scheduler.startReminderThread();
    } else if (command == "help") {
        showHelp();
    } else if (command == "exit") {
        std::cout << "Exiting..." << std::endl;
        scheduler.stopReminderThread();
        exit(0);
    } else {
        std::cout << "Unknown command. Type 'help' for available commands." << std::endl;
    }
}

void CommandLineInterface::runShellMode() {
    // 加载任务数据
    if (taskManager.loadFromFile("../data/tasks.txt")) {
        std::cout << "Tasks loaded from file." << std::endl;
    } else {
        std::cerr << "Failed to load tasks from file. Please check the file format or path." << std::endl;
    }

    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        std::istringstream iss(input);
        std::vector<std::string> args;
        std::string arg;
        while (iss >> arg) {
            args.push_back(arg);
        }
        handleCommand(args);
    }
}