#include "TaskListDialog.h"
#include <QTableWidget>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <algorithm>

TaskListDialog::TaskListDialog(const std::vector<Task>& tasks, QWidget* parent)
    : QDialog(parent), allTasks(tasks) {
    setWindowTitle(QString::fromUtf8("Task List"));
    setModal(true);
    resize(800, 500);
    
    setupUI();
    populateTable(allTasks);
}

void TaskListDialog::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    // 排序控件
    QHBoxLayout* sortLayout = new QHBoxLayout();
    sortLayout->addWidget(new QLabel(QString::fromUtf8("排序方式:"), this));
    
    sortComboBox = new QComboBox(this);
    sortComboBox->addItem(QString::fromUtf8("按ID排序"), "id");
    sortComboBox->addItem(QString::fromUtf8("按开始时间排序"), "start_time");
    sortComboBox->addItem(QString::fromUtf8("按提醒时间排序"), "reminder_time");
    sortLayout->addWidget(sortComboBox);
    
    refreshButton = new QPushButton(QString::fromUtf8("刷新排序"), this);
    sortLayout->addWidget(refreshButton);
    
    sortLayout->addStretch();
    mainLayout->addLayout(sortLayout);
    
    // 任务表格
    taskTable = new QTableWidget(this);
    taskTable->setColumnCount(6);
    
    QStringList headers;
    headers << QString::fromUtf8("ID") 
            << QString::fromUtf8("任务名称") 
            << QString::fromUtf8("开始时间") 
            << QString::fromUtf8("分类") 
            << QString::fromUtf8("优先级") 
            << QString::fromUtf8("提醒时间");
    taskTable->setHorizontalHeaderLabels(headers);
    
    // 设置表格属性
    taskTable->setAlternatingRowColors(true);
    taskTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    taskTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    taskTable->horizontalHeader()->setStretchLastSection(true);
    
    mainLayout->addWidget(taskTable);
    
    // 按钮布局
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    
    closeButton = new QPushButton(QString::fromUtf8("关闭"), this);
    buttonLayout->addWidget(closeButton);
    
    mainLayout->addLayout(buttonLayout);
    
    // 连接信号和槽
    connect(refreshButton, &QPushButton::clicked, this, &TaskListDialog::sortTasks);
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(sortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &TaskListDialog::sortTasks);
}

void TaskListDialog::populateTable(const std::vector<Task>& tasks) {
    taskTable->setRowCount(tasks.size());
    
    for (size_t i = 0; i < tasks.size(); ++i) {
        const Task& task = tasks[i];
        
        // ID
        QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(task.getId()));
        taskTable->setItem(i, 0, idItem);
        
        // 任务名称
        QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromUtf8(task.getName().c_str()));
        taskTable->setItem(i, 1, nameItem);
        
        // 开始时间
        QTableWidgetItem* startTimeItem = new QTableWidgetItem(QString::fromUtf8(task.getStartTime().c_str()));
        taskTable->setItem(i, 2, startTimeItem);
        
        // 分类
        QTableWidgetItem* categoryItem = new QTableWidgetItem(QString::fromUtf8(task.getCategory().c_str()));
        taskTable->setItem(i, 3, categoryItem);
        
        // 优先级
        QTableWidgetItem* priorityItem = new QTableWidgetItem(QString::fromUtf8(task.getPriority().c_str()));
        taskTable->setItem(i, 4, priorityItem);
        
        // 提醒时间
        QTableWidgetItem* reminderTimeItem = new QTableWidgetItem(QString::fromUtf8(task.getReminderTime().c_str()));
        taskTable->setItem(i, 5, reminderTimeItem);
        
        // 根据优先级设置行颜色
        QColor rowColor;
        if (task.getPriority() == "高" || task.getPriority() == "High") {
            rowColor = QColor(255, 200, 200); // 浅红色
        } else if (task.getPriority() == "中" || task.getPriority() == "Middle") {
            rowColor = QColor(255, 255, 200); // 浅黄色
        } else if (task.getPriority() == "低" || task.getPriority() == "Low") {
            rowColor = QColor(200, 255, 200); // 浅绿色
        } else {
            rowColor = QColor(240, 240, 240); // 默认灰色
        }
        
        for (int j = 0; j < 6; ++j) {
            taskTable->item(i, j)->setBackground(rowColor);
        }
    }
    
    // 调整列宽
    taskTable->resizeColumnsToContents();
}

void TaskListDialog::sortTasks() {
    std::string sortBy = sortComboBox->currentData().toString().toStdString();
    std::vector<Task> sortedTasks = allTasks;
    
    if (sortBy == "id") {
        std::sort(sortedTasks.begin(), sortedTasks.end(), 
                  [](const Task& a, const Task& b) {
                      return a.getId() < b.getId();
                  });
    } else if (sortBy == "start_time") {
        std::sort(sortedTasks.begin(), sortedTasks.end(), 
                  [](const Task& a, const Task& b) {
                      return a.getStartTime() < b.getStartTime();
                  });
    } else if (sortBy == "reminder_time") {
        std::sort(sortedTasks.begin(), sortedTasks.end(), 
                  [](const Task& a, const Task& b) {
                      return a.getReminderTime() < b.getReminderTime();
                  });
    }
    
    populateTable(sortedTasks);
}

void TaskListDialog::refreshTable() {
    populateTable(allTasks);
}
