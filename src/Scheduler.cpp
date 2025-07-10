#include "Scheduler.h"
#include "Utils.h"
#include <iostream>
#include <chrono>
#include <ctime>

Scheduler::Scheduler(TaskManager& taskManager)
    : taskManager(taskManager), running(false) {}

Scheduler::~Scheduler() {
    stopReminderThread();
}

void Scheduler::startReminderThread() {
    running = true;
    reminderThread = std::thread(&Scheduler::checkReminders, this);
}

void Scheduler::stopReminderThread() {
    running = false;
    if (reminderThread.joinable()) {
        reminderThread.join();
    }
}

void Scheduler::checkReminders() {
    while (running) {
        // 获取当前系统时间
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);

        // 遍历所有任务，检查是否需要提醒
        auto tasks = taskManager.getAllTasks();
        for (const auto& task : tasks) {
            std::tm reminder_tm = stringToTime(task.getReminderTime());
            std::time_t reminder_time = tmToTimeT(reminder_tm);

            //std::cout << "Reminder Time: " << reminder_time << ", Current Time: " << now_time << std::endl;

            // 检查提醒时间是否在当前时间的前后 30 秒内
            if (std::abs(difftime(reminder_time, now_time)) <= 30) {
                std::cout << "Reminder: " << task.toString() << std::endl;
            }
        }

        // 每分钟检查一次
        std::this_thread::sleep_for(std::chrono::seconds(30));
}
}
