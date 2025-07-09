#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
public:
    Task(int id, const std::string& name, const std::string& start_time,
         const std::string& category = "生活", const std::string& priority = "中",
         const std::string& reminder_time = "");

    bool isValid() const;
    std::string toString() const;

    int getId() const;
    std::string getName() const;
    std::string getStartTime() const;

private:
    int id;
    std::string name;
    std::string start_time;
    std::string category;
    std::string priority;
    std::string reminder_time;
};

#endif // TASK_H