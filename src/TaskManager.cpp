#include "TaskManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

void TaskManager::addTask(const Task& task) {
    tasks.push_back(task);
}

void TaskManager::deleteTask(int id) {
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->getId() == id) {
            tasks.erase(it);
            return; // 删除后直接退出，避免迭代器失效
        }
    }
}

std::vector<Task> TaskManager::getTasksByDate(const std::string& date) const {
    std::vector<Task> result;
    for (const auto& task : tasks) {
        if (task.getStartTime().find(date) != std::string::npos) {
            result.push_back(task);
        }
    }
    return result;
}

void TaskManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for saving: " << filename << std::endl;
        return;
    }

    for (const auto& task : tasks) {
        file << task.toString() << std::endl;
    }

    file.close();
    std::cout << "Tasks successfully saved to " << filename << std::endl;
}

void TaskManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for loading: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int id;
        std::string name, start_time, category, priority, reminder_time;

        // 检查是否能够正确解析任务数据
        if (!(iss >> id >> name >> start_time >> category >> priority >> reminder_time)) {
            std::cerr << "Error: Malformed task data in file: " << line << std::endl;
            continue; // 跳过错误数据
        }

        tasks.emplace_back(id, name, start_time, category, priority, reminder_time);
    }

    file.close();
    std::cout << "Tasks successfully loaded from " << filename << std::endl;
}