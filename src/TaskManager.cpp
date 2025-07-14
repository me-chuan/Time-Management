#include "TaskManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Utils.h"

void TaskManager::addTask(const Task& task) {
    tasks.push_back(task);
}

void TaskManager::deleteTask(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
                           [id](const Task& task) { return task.getId() == id; });
    if (it != tasks.end()) {
        tasks.erase(it);
        std::cout << "Task with ID " << id << " deleted successfully." << std::endl;
    } else {
        throw std::runtime_error("Task with ID " + std::to_string(id) + " not found.");
    }
}

void TaskManager::editTask(int id, const Task& updatedTask) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
                           [id](const Task& task) { return task.getId() == id; });
    if (it != tasks.end()) {
        // 保持原有的ID，更新其他属性
        it->setName(updatedTask.getName());
        it->setStartTime(updatedTask.getStartTime());
        it->setReminderTime(updatedTask.getReminderTime());
        it->setCategory(updatedTask.getCategory());
        it->setPriority(updatedTask.getPriority());
        it->setDone(updatedTask.isDone());
        std::cout << "Task with ID " << id << " updated successfully." << std::endl;
    } else {
        throw std::runtime_error("Task with ID " + std::to_string(id) + " not found.");
    }
}

void TaskManager::finishTask(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
                           [id](const Task& task) { return task.getId() == id; });
    if (it != tasks.end()) {
        it->setDone(true);
        std::cout << "Task with ID " << id << " marked as completed." << std::endl;
    } else {
        throw std::runtime_error("Task with ID " + std::to_string(id) + " not found.");
    }
}

Task* TaskManager::findTaskById(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
                           [id](const Task& task) { return task.getId() == id; });
    return (it != tasks.end()) ? &(*it) : nullptr;
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

    tasks.clear(); // 清空现有任务
    std::string line;
    while (std::getline(file, line)) {
        // 跳过空行
        if (line.empty()) {
            continue;
        }

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
            // 正确计算字符串提取的起始位置和长度
            int id = std::stoi(line.substr(id_pos + 4, name_pos - (id_pos + 4)));
            
            std::string name = line.substr(name_pos + 8, start_time_pos - (name_pos + 8));
            
            std::string start_time = line.substr(start_time_pos + 14, category_pos - (start_time_pos + 14));
            
            std::string category = line.substr(category_pos + 12, priority_pos - (category_pos + 12));
            
            std::string priority = line.substr(priority_pos + 12, reminder_time_pos - (priority_pos + 12));
            
            std::string reminder_time = line.substr(reminder_time_pos + 17);
            
            // 检查是否有完成状态标记
            bool isDone = false;
            size_t completed_pos = reminder_time.find(" [COMPLETED]");
            if (completed_pos != std::string::npos) {
                isDone = true;
                reminder_time = reminder_time.substr(0, completed_pos);
            }

            // 去除字符串前后的空格
            name = trim(name);
            start_time = trim(start_time);
            category = trim(category);
            priority = trim(priority);
            reminder_time = trim(reminder_time);

            Task task(id, name, start_time, category, priority, reminder_time);
            task.setDone(isDone);
            tasks.emplace_back(task);
        } catch (const std::exception& e) {
            std::cerr << "Error: Failed to parse task data in file: " << line << std::endl;
            continue; // 跳过错误数据
        }
    }

    file.close();
    std::cout << "Tasks successfully loaded from " << filename << std::endl;
    return true; // 添加这个return语句
}

int TaskManager::getMaxTaskId() const {
    int maxId = 0;
    for (const auto& task : tasks) {
        if (task.getId() > maxId) {
            maxId = task.getId();
        }
    }
    return maxId;
}