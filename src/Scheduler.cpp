#include "Scheduler.h"
#include <iostream>
#include <chrono>

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
        auto tasks = taskManager.getTasksByDate("2025-07-10"); // Example date
        for (const auto& task : tasks) {
            std::cout << "Reminder: " << task.toString() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(60));
    }
}
