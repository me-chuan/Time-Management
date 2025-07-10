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
    std::cerr << "Error: Task with ID " << id << " not found." << std::endl;
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

std::vector<Task> TaskManager::getAllTasks() const {
    return tasks; // 返回所有任务
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

bool TaskManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for loading: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        // 使用分隔符解析任务数据
        size_t id_pos = line.find("ID: ");
        size_t name_pos = line.find(", Name: ");
        size_t start_time_pos = line.find(", Start Time: ");
        size_t category_pos = line.find(", Category: ");
        size_t priority_pos = line.find(", Priority: ");
        size_t reminder_time_pos = line.find(", Reminder Time: ");

        if (id_pos == std::string::npos || name_pos == std::string::npos ||
            start_time_pos == std::string::npos || category_pos == std::string::npos ||
            priority_pos == std::string::npos || reminder_time_pos == std::string::npos) {
            std::cerr << "Error: Malformed task data in file: " << line << std::endl;
            continue; // 跳过错误数据
        }

        try {
            int id = std::stoi(line.substr(id_pos + 4, name_pos - (id_pos + 4)));
            std::string name = line.substr(name_pos + 8, start_time_pos - (name_pos + 8));
            std::string start_time = line.substr(start_time_pos + 13, category_pos - (start_time_pos + 13));
            std::string category = line.substr(category_pos + 11, priority_pos - (category_pos + 11));
            std::string priority = line.substr(priority_pos + 11, reminder_time_pos - (priority_pos + 11));
            std::string reminder_time = line.substr(reminder_time_pos + 15);

            tasks.emplace_back(id, name, start_time, category, priority, reminder_time);
        } catch (const std::exception& e) {
            std::cerr << "Error: Failed to parse task data in file: " << line << std::endl;
            continue; // 跳过错误数据
        }
    }

    file.close();
    std::cout << "Tasks successfully loaded from " << filename << std::endl;
    return true;
}