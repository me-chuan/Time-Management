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

    // 添加 getter 方法
    int getId() const;
    std::string getName() const;
    std::string getStartTime() const;
    std::string getCategory() const;
    std::string getPriority() const;
    std::string getReminderTime() const;
    bool isDone() const;
    
    // 添加 setter 方法
    void setName(const std::string& name);
    void setStartTime(const std::string& start_time);
    void setCategory(const std::string& category);
    void setPriority(const std::string& priority);
    void setReminderTime(const std::string& reminder_time);
    void setDone(bool done);

private:
    int id;
    std::string name;
    std::string start_time;
    std::string category;
    std::string priority;
    std::string reminder_time;
    bool done = false;
};

#endif // TASK_H