#include "AddTaskDialog.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateTimeEdit>
#include <QDateTime>
#include <QComboBox>
#include <QTextCodec>

AddTaskDialog::AddTaskDialog(QWidget* parent)
    : QDialog(parent) {
    setWindowTitle(QString("Add New Task")); 
    setModal(true);
    
    // 设置窗口大小
    setFixedSize(600, 450);

    QVBoxLayout* layout = new QVBoxLayout(this);

    // Task Name
    layout->addWidget(new QLabel(QString::fromUtf8("任务名称:"), this));
    taskNameInput = new QLineEdit(this);
    taskNameInput->setPlaceholderText(QString::fromUtf8("请输入任务名称"));
    layout->addWidget(taskNameInput);

    // Start Time
    layout->addWidget(new QLabel(QString::fromUtf8("开始时间:"), this));
    startTimeInput = new QDateTimeEdit(this);
    startTimeInput->setDisplayFormat("yyyy-MM-dd hh:mm");
    startTimeInput->setDateTime(QDateTime::currentDateTime());
    startTimeInput->setCalendarPopup(true);
    layout->addWidget(startTimeInput);

    // Reminder Time
    layout->addWidget(new QLabel(QString::fromUtf8("提醒时间:"), this));
    reminderTimeInput = new QDateTimeEdit(this);
    reminderTimeInput->setDisplayFormat("yyyy-MM-dd hh:mm");
    reminderTimeInput->setDateTime(QDateTime::currentDateTime().addSecs(-600));
    reminderTimeInput->setCalendarPopup(true);
    layout->addWidget(reminderTimeInput);

    // Category
    layout->addWidget(new QLabel(QString::fromUtf8("分类 (可选, 默认: None):"), this));
    categoryInput = new QLineEdit(this);
    categoryInput->setPlaceholderText(QString::fromUtf8("Study, Work, Life, Health, Entertainment"));
    layout->addWidget(categoryInput);

    // Priority
    layout->addWidget(new QLabel(QString::fromUtf8("优先级 (可选, 默认: Middle):"), this));
    priorityInput = new QLineEdit(this);
    priorityInput->setPlaceholderText(QString::fromUtf8("High, Middle, Low"));
    layout->addWidget(priorityInput);

    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    submitButton = new QPushButton(QString::fromUtf8("添加任务"), this);
    cancelButton = new QPushButton(QString::fromUtf8("取消"), this);
    
    buttonLayout->addWidget(submitButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    connect(submitButton, &QPushButton::clicked, this, &AddTaskDialog::handleSubmit);
    connect(cancelButton, &QPushButton::clicked, this, &AddTaskDialog::handleCancel);
}

void AddTaskDialog::handleSubmit() {
    taskName = taskNameInput->text().toUtf8().toStdString();
    
    // 将 QDateTime 转换为你需要的格式
    QDateTime startDT = startTimeInput->dateTime();
    QDateTime reminderDT = reminderTimeInput->dateTime();
    
    startTime = startDT.toString("yyyy-MM-dd_hh:mm").toStdString();
    reminderTime = reminderDT.toString("yyyy-MM-dd_hh:mm").toStdString();
    
    category = categoryInput->text().toUtf8().toStdString();
    priority = priorityInput->text().toUtf8().toStdString();
    
    accept();
}

void AddTaskDialog::handleCancel() {
    reject();
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