#include "CommandLineInterface.h"
#include <iostream>
#include <sstream>

CommandLineInterface::CommandLineInterface(TaskManager& taskManager, Scheduler& scheduler)
    : taskManager(taskManager), scheduler(scheduler) {}

void CommandLineInterface::showHelp() const {
    std::cout << "Available commands:\n"
              << "  addtask <id> <name> <start_time> <category> <priority> <reminder_time>\n"
              << "  deltask <id>\n"
              << "  showtask\n"
              << "  run\n"
              << "  help\n"
              << "  exit\n";
}

void CommandLineInterface::handleCommand(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << "No command provided. Type 'help' for available commands." << std::endl;
        return;
    }

    const std::string& command = args[0];
    if (command == "addtask" && args.size() == 7) {
        int id = std::stoi(args[1]);
        taskManager.addTask(Task(id, args[2], args[3], args[4], args[5], args[6]));
        taskManager.saveToFile("../data/tasks.txt"); // 保存任务数据到文件
        std::cout << "Task added and saved to file." << std::endl;
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