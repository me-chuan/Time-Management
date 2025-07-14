#include "EditTaskDialog.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateTimeEdit>
#include <QDateTime>
#include <QCheckBox>

EditTaskDialog::EditTaskDialog(const Task& task, QWidget* parent)
    : QDialog(parent) {
    setWindowTitle(QString::fromUtf8("编辑任务"));
    setModal(true);
    
    // 设置窗口大小
    setFixedSize(400, 400);

    QVBoxLayout* layout = new QVBoxLayout(this);

    // Task Name
    layout->addWidget(new QLabel(QString::fromUtf8("任务名称:"), this));
    taskNameInput = new QLineEdit(this);
    taskNameInput->setText(QString::fromUtf8(task.getName().c_str()));
    layout->addWidget(taskNameInput);

    // Start Time
    layout->addWidget(new QLabel(QString::fromUtf8("开始时间:"), this));
    startTimeInput = new QDateTimeEdit(this);
    startTimeInput->setDisplayFormat("yyyy-MM-dd hh:mm");
    
    // 解析现有时间
    QString timeStr = QString::fromStdString(task.getStartTime());
    timeStr.replace('_', ' ');
    QDateTime startDT = QDateTime::fromString(timeStr, "yyyy-MM-dd hh:mm");
    if (startDT.isValid()) {
        startTimeInput->setDateTime(startDT);
    } else {
        startTimeInput->setDateTime(QDateTime::currentDateTime());
    }
    startTimeInput->setCalendarPopup(true);
    layout->addWidget(startTimeInput);

    // Reminder Time
    layout->addWidget(new QLabel(QString::fromUtf8("提醒时间:"), this));
    reminderTimeInput = new QDateTimeEdit(this);
    reminderTimeInput->setDisplayFormat("yyyy-MM-dd hh:mm");
    
    // 解析现有提醒时间
    QString reminderStr = QString::fromStdString(task.getReminderTime());
    reminderStr.replace('_', ' ');
    QDateTime reminderDT = QDateTime::fromString(reminderStr, "yyyy-MM-dd hh:mm");
    if (reminderDT.isValid()) {
        reminderTimeInput->setDateTime(reminderDT);
    } else {
        reminderTimeInput->setDateTime(QDateTime::currentDateTime().addSecs(-600));
    }
    reminderTimeInput->setCalendarPopup(true);
    layout->addWidget(reminderTimeInput);

    // Category
    layout->addWidget(new QLabel(QString::fromUtf8("分类:"), this));
    categoryInput = new QLineEdit(this);
    categoryInput->setText(QString::fromUtf8(task.getCategory().c_str()));
    categoryInput->setPlaceholderText(QString::fromUtf8("学习, 工作, 生活, 健康, 娱乐"));
    layout->addWidget(categoryInput);

    // Priority
    layout->addWidget(new QLabel(QString::fromUtf8("优先级:"), this));
    priorityInput = new QLineEdit(this);
    priorityInput->setText(QString::fromUtf8(task.getPriority().c_str()));
    priorityInput->setPlaceholderText(QString::fromUtf8("高, 中, 低"));
    layout->addWidget(priorityInput);

    // Done status
    doneCheckBox = new QCheckBox(QString::fromUtf8("已完成"), this);
    doneCheckBox->setChecked(task.isDone());
    layout->addWidget(doneCheckBox);

    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    submitButton = new QPushButton(QString::fromUtf8("保存"), this);
    cancelButton = new QPushButton(QString::fromUtf8("取消"), this);
    
    buttonLayout->addWidget(submitButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    connect(submitButton, &QPushButton::clicked, this, &EditTaskDialog::handleSubmit);
    connect(cancelButton, &QPushButton::clicked, this, &EditTaskDialog::handleCancel);
}

void EditTaskDialog::handleSubmit() {
    taskName = taskNameInput->text().toUtf8().toStdString();
    
    // 将 QDateTime 转换为你需要的格式
    QDateTime startDT = startTimeInput->dateTime();
    QDateTime reminderDT = reminderTimeInput->dateTime();
    
    startTime = startDT.toString("yyyy-MM-dd_hh:mm").toStdString();
    reminderTime = reminderDT.toString("yyyy-MM-dd_hh:mm").toStdString();
    
    category = categoryInput->text().toUtf8().toStdString();
    priority = priorityInput->text().toUtf8().toStdString();
    isDone = doneCheckBox->isChecked();
    
    accept();
}

void EditTaskDialog::handleCancel() {
    reject();
}

std::string EditTaskDialog::getTaskName() const {
    return taskName;
}

std::string EditTaskDialog::getStartTime() const {
    return startTime;
}

std::string EditTaskDialog::getReminderTime() const {
    return reminderTime;
}

std::string EditTaskDialog::getCategory() const {
    return category;
}

std::string EditTaskDialog::getPriority() const {
    return priority;
}

bool EditTaskDialog::getIsDone() const {
    return isDone;
}
