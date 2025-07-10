#include "Task.h"
#include "User.h"
#include <iostream>

int main() {
    // 测试 User 类
    User user("test_user", "password123");
    if (user.authenticate("test_user", "password123")) {
        std::cout << "User authentication successful!" << std::endl;
    } else {
        std::cout << "User authentication failed!" << std::endl;
    }

    // 测试 Task 类
    Task task(1, "Study C++", "2025-07-10 10:00", "学习", "高", "2025-07-10 09:50");
    if (task.isValid()) {
        std::cout << "Task is valid!" << std::endl;
        std::cout << task.toString() << std::endl;
    } else {
        std::cout << "Task is invalid!" << std::endl;
    }

    return 0;
}
