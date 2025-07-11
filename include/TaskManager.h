#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include "Task.h"
#include <vector>
#include <string>

class TaskManager {
public:
    void addTask(const Task& task);
    void deleteTask(int id);
    std::vector<Task> getTasksByDate(const std::string& date) const;
    std::vector<Task> getAllTasks() const; // 新增方法
    void saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
    int getMaxTaskId() const; // 新增方法

private:
    std::vector<Task> tasks;
};

#endif // TASKMANAGER_H
