#ifndef COMMANDLINEINTERFACE_H
#define COMMANDLINEINTERFACE_H

#include "TaskManager.h"
#include "Scheduler.h"
#include <vector>
#include <string>

class CommandLineInterface {
public:
    CommandLineInterface(TaskManager& taskManager, Scheduler& scheduler);
    void showHelp() const;
    void handleCommand(const std::vector<std::string>& args);
    void runShellMode();

private:
    TaskManager& taskManager;
    Scheduler& scheduler;
    int nextId; // 将 nextId 定义为类的成员变量
};

#endif // COMMANDLINEINTERFACE_H
