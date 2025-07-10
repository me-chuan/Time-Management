#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "TaskManager.h"
#include <thread>
#include <atomic>

class Scheduler {
public:
    Scheduler(TaskManager& taskManager);
    ~Scheduler();

    void startReminderThread();
    void stopReminderThread();

private:
    void checkReminders();

    TaskManager& taskManager;
    std::thread reminderThread;
    std::atomic<bool> running;
};

#endif // SCHEDULER_H
