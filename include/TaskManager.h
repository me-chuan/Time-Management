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
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

private:
    std::vector<Task> tasks;
};

#endif // TASKMANAGER_H
