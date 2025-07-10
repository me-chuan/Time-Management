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
    for (const auto& task : tasks) {
        file << task.toString() << std::endl;
    }
}

void TaskManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int id;
        std::string name, start_time, category, priority, reminder_time;
        iss >> id >> name >> start_time >> category >> priority >> reminder_time;
        tasks.emplace_back(id, name, start_time, category, priority, reminder_time);
    }
}
