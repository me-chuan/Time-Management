#include "AddTaskDialog.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

AddTaskDialog::AddTaskDialog(QWidget* parent)
    : QDialog(parent) {
    setWindowTitle("Add New Task");
    setModal(true);

    QVBoxLayout* layout = new QVBoxLayout(this);

    // Task Name
    layout->addWidget(new QLabel("Task Name:", this));
    taskNameInput = new QLineEdit(this);
    taskNameInput->setPlaceholderText("Enter task name");
    layout->addWidget(taskNameInput);

    // Start Time
    layout->addWidget(new QLabel("Start Time (YYYY-MM-DD_HH:MM):", this));
    startTimeInput = new QLineEdit(this);
    startTimeInput->setPlaceholderText("2025-07-15_10:00");
    layout->addWidget(startTimeInput);

    // Reminder Time
    layout->addWidget(new QLabel("Reminder Time (YYYY-MM-DD_HH:MM):", this));
    reminderTimeInput = new QLineEdit(this);
    reminderTimeInput->setPlaceholderText("2025-07-15_09:50");
    layout->addWidget(reminderTimeInput);

    // Category
    layout->addWidget(new QLabel("Category (Optional, default: 未分类):", this));
    categoryInput = new QLineEdit(this);
    categoryInput->setPlaceholderText("学习, 工作, 生活, etc.");
    layout->addWidget(categoryInput);

    // Priority
    layout->addWidget(new QLabel("Priority (Optional, default: 中):", this));
    priorityInput = new QLineEdit(this);
    priorityInput->setPlaceholderText("高, 中, 低");
    layout->addWidget(priorityInput);

    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    submitButton = new QPushButton("Add Task", this);
    cancelButton = new QPushButton("Cancel", this);
    
    buttonLayout->addWidget(submitButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    connect(submitButton, &QPushButton::clicked, this, &AddTaskDialog::handleSubmit);
    connect(cancelButton, &QPushButton::clicked, this, &AddTaskDialog::handleCancel);
}

void AddTaskDialog::handleSubmit() {
    taskName = taskNameInput->text().toStdString();
    startTime = startTimeInput->text().toStdString();
    reminderTime = reminderTimeInput->text().toStdString();
    category = categoryInput->text().toStdString();
    priority = priorityInput->text().toStdString();
    accept(); // 关闭对话框并返回 Accepted
}

void AddTaskDialog::handleCancel() {
    reject(); // 关闭对话框并返回 Rejected
}

std::string AddTaskDialog::getTaskName() const {
    return taskName;
}

std::string AddTaskDialog::getStartTime() const {
    return startTime;
}

std::string AddTaskDialog::getReminderTime() const {
    return reminderTime;
}

std::string AddTaskDialog::getCategory() const {
    return category;
}

std::string AddTaskDialog::getPriority() const {
    return priority;
}