#include "Task.h"
#include <sstream>

Task::Task(int id, const std::string& name, const std::string& start_time,
           const std::string& category, const std::string& priority,
           const std::string& reminder_time)
    : id(id), name(name), start_time(start_time), category(category),
      priority(priority), reminder_time(reminder_time) {}

bool Task::isValid() const {
    // 检查任务名称和开始时间是否为空
    return !name.empty() && !start_time.empty();
}

std::string Task::toString() const {
    std::ostringstream oss;
    oss << "ID: " << id << ", Name: " << name << ", Start Time: " << start_time
        << ", Category: " << category << ", Priority: " << priority
        << ", Reminder Time: " << reminder_time;
    return oss.str();
}

// 添加 getter 方法的实现
int Task::getId() const {
    return id;
}

std::string Task::getName() const {
    return name;
}

std::string Task::getStartTime() const {
    return start_time;
}

std::string Task::getCategory() const {
    return category;
}

std::string Task::getPriority() const {
    return priority;
}

std::string Task::getReminderTime() const {
    return reminder_time;
}