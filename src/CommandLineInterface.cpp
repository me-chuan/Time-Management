#include "CommandLineInterface.h"
#include <iostream>
#include <sstream>
#include  "Utils.h"
#include <QApplication>
#include "AddTaskDialog.h"

CommandLineInterface::CommandLineInterface(TaskManager& taskManager, Scheduler& scheduler)
    : taskManager(taskManager), scheduler(scheduler) {}

void CommandLineInterface::showHelp() const {
    std::cout << "Available commands:\n"
              << "  addtask <name> <start_time> <reminder_time> [-c <category>] [-p <priority>]\n"
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
    if (command == "addtask") {
        // 创建并显示图形界面对话框
        AddTaskDialog dialog;
        if (dialog.exec() == QDialog::Accepted) {
            std::string name = dialog.getTaskName();
            std::string start_time = dialog.getStartTime();
            std::string reminder_time = dialog.getReminderTime();
            std::string category = dialog.getCategory();
            std::string priority = dialog.getPriority();

            // 如果用户没有输入分类或优先级，使用默认值
            if (category.empty()) {
                category = "未分类";
            }
            if (priority.empty()) {
                priority = "中";
            }

            try {
                if (name.empty()) {
                    throw std::invalid_argument("Task name cannot be empty.");
                }
                if (!isValidTimeFormat(start_time)) {
                    throw std::invalid_argument("Invalid start time format. Expected format: YYYY-MM-DD_HH:MM.");
                }
                if (!isValidTimeFormat(reminder_time)) {
                    throw std::invalid_argument("Invalid reminder time format. Expected format: YYYY-MM-DD_HH:MM.");
                }

                // 自动生成任务 ID 并添加任务
                int id = ++nextId;
                taskManager.addTask(Task(id, name, start_time, category, priority, reminder_time));
                taskManager.saveToFile("../data/tasks.txt");
                std::cout << "Task added with ID " << id << " and saved to file." << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error adding task: " << e.what() << std::endl;
            }
        } else {
            std::cout << "Task creation cancelled." << std::endl;
        }
    } else if (command == "deltask" && args.size() == 2) {
        // 保留原有的 deltask 逻辑
        try {
            int id = std::stoi(args[1]);
            taskManager.deleteTask(id);
            taskManager.saveToFile("../data/tasks.txt");
            std::cout << "Task with ID " << id << " deleted and saved to file." << std::endl;

            // 如果删除的是最后一个任务，调整 nextId
            if (id == nextId) {
                --nextId;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error deleting task: " << e.what() << std::endl;
        }
    } else if (command == "showtask") {
        auto tasks = taskManager.getAllTasks();
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

        // 动态设置 nextId 为当前任务列表中的最大 ID + 1
        int maxId = taskManager.getMaxTaskId();
        nextId = maxId;
        //std::cout << "Next task ID set to " << nextId << "." << std::endl;
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