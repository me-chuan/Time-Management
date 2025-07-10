#include "CommandLineInterface.h"
#include <iostream>
#include <sstream>

CommandLineInterface::CommandLineInterface(TaskManager& taskManager, Scheduler& scheduler)
    : taskManager(taskManager), scheduler(scheduler) {}

void CommandLineInterface::showHelp() const {
    std::cout << "Available commands:\n"
              << "  addtask <id> <name> <start_time> <category> <priority> <reminder_time>\n"
              << "  deltask <id>\n"
              << "  showtask <date>\n"
              << "  run\n"
              << "  help\n";
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
    } else if (command == "deltask" && args.size() == 2) {
        int id = std::stoi(args[1]);
        taskManager.deleteTask(id);
    } else if (command == "showtask" && args.size() == 2) {
        auto tasks = taskManager.getTasksByDate(args[1]);
        for (const auto& task : tasks) {
            std::cout << task.toString() << std::endl;
        }
    } else if (command == "run") {
        scheduler.startReminderThread();
    } else if (command == "help") {
        showHelp();
    } else {
        std::cout << "Unknown command. Type 'help' for available commands." << std::endl;
    }
}

void CommandLineInterface::runShellMode() {
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
