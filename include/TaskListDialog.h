#ifndef TASKLISTDIALOG_H
#define TASKLISTDIALOG_H

#include <QDialog>
#include <vector>
#include "Task.h"

class QTableWidget;
class QPushButton;
class QComboBox;

class TaskListDialog : public QDialog {
    Q_OBJECT

public:
    explicit TaskListDialog(const std::vector<Task>& tasks, QWidget* parent = nullptr);

private slots:
    void sortTasks();
    void refreshTable();

private:
    void setupUI();
    void populateTable(const std::vector<Task>& tasks);
    
    QTableWidget* taskTable;
    QPushButton* refreshButton;
    QPushButton* closeButton;
    QComboBox* sortComboBox;
    
    std::vector<Task> allTasks;
};

#endif // TASKLISTDIALOG_H
