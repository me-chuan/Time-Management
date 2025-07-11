#include "TaskManager.h"
#include "Scheduler.h"
#include "CommandLineInterface.h"
#include "User.h"
#include <iostream>
#include <map>
#include <fstream>

const std::string USER_FILE = "../data/users.txt";

// 保存用户数据到文件
void saveUsersToFile(const std::map<std::string, User>& users) {
    std::ofstream file(USER_FILE);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open user file for saving!" << std::endl;
        return;
    }

    for (const auto& [username, user] : users) {
        file << username << " " << user.getPasswordHash() << std::endl;
    }

    file.close();
}

// 从文件加载用户数据
std::map<std::string, User> loadUsersFromFile() {
    std::map<std::string, User> users;
    std::ifstream file(USER_FILE);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open user file for loading!" << std::endl;
        // 如果文件不存在，返回一个空的用户列表
        return users;
    }

    std::string username, passwordHash;
    while (file >> username >> passwordHash) {
        users[username] = User(username, passwordHash); // 使用特殊构造函数加载用户
    }

    file.close();
    return users;
}

int main() {
    // 用户管理
    std::map<std::string, User> users = loadUsersFromFile();

    std::cout << "Welcome to the Schedule Management System!" << std::endl;

    while (true) {
        std::cout << "Please choose an option: [register/login/deleteuser/exit]: ";
        std::string option;
        std::cin >> option;

        if (option == "register") {
            std::string username, password;
            std::cout << "Enter username: ";
            std::cin >> username;
            std::cout << "Enter password: ";
            std::cin >> password;

            if (users.find(username) != users.end()) {
                std::cout << "Error: Username already exists!" << std::endl;
            } else {
                users[username] = User(username, password);
                saveUsersToFile(users); // 保存到文件
                std::cout << "Registration successful!" << std::endl;
            }
        } else if (option == "login") {
            std::string username, password;
            std::cout << "Enter username: ";
            std::cin >> username;
            std::cout << "Enter password: ";
            std::cin >> password;

            auto it = users.find(username);
            if (it != users.end() && it->second.authenticate(username, password)) {
                std::cout << "Login successful!" << std::endl;

                // 创建 TaskManager 实例
                TaskManager taskManager;

                // 创建 Scheduler 实例
                Scheduler scheduler(taskManager);

                // 创建 CommandLineInterface 实例
                CommandLineInterface cli(taskManager, scheduler);

                // 加载任务数据
                if (taskManager.loadFromFile("../data/tasks.txt")) {
                    std::cout << "Tasks loaded from file." << std::endl;
                } else {
                    std::cerr << "Failed to load tasks from file. Please check the file format or path." << std::endl;
                }

                // 进入命令行交互模式
                cli.runShellMode();

                return 0; // 退出程序
            } else {
                std::cout << "Error: Invalid username or password!" << std::endl;
            }
        } else if (option == "delete") {
            std::string username, password;
            std::cout << "Enter username: ";
            std::cin >> username;
            std::cout << "Enter password: ";
            std::cin >> password;

            auto it = users.find(username);
            if (it != users.end() && it->second.authenticate(username, password)) {
                users.erase(username); // 删除用户
                saveUsersToFile(users); // 保存到文件
                std::cout << "User deleted successfully!" << std::endl;
            } else {
                std::cout << "Error: Invalid username or password!" << std::endl;
            }
        } else if (option == "exit") {
            std::cout << "Exiting the program. Goodbye!" << std::endl;
            return 0;
        } else {
            std::cout << "Invalid option. Please choose [register/login/deleteuser/exit]." << std::endl;
        }
    }
}