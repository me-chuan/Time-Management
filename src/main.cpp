#include "TaskManager.h"
#include "Scheduler.h"
#include "CommandLineInterface.h"
#include "User.h"
#include <iostream>
#include <map>
#include <fstream>
#include <QApplication>  // 添加Qt应用程序支持

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

std::map<std::string, User> loadUsersFromFile() {
    std::map<std::string, User> users;
    std::ifstream file(USER_FILE);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open user file for loading!" << std::endl;
        return users;
    }

    std::string username, passwordHash;
    while (file >> username >> passwordHash) {
        // 使用特殊构造函数加载用户，直接保存哈希值
        users[username] = User(username, passwordHash, true); // 第三个参数表示密码已经是哈希值
    }

    file.close();
    //std::cout << "Total users loaded: " << users.size() << std::endl;
    return users;
}

int main(int argc, char* argv[]) {  // 修改main函数签名以支持Qt
    // 初始化Qt应用程序
    QApplication app(argc, argv);
    
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