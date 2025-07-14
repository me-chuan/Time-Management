#ifndef ADDTASKDIALOG_H
#define ADDTASKDIALOG_H

#include <QDialog>
#include <string>

class QLineEdit;
class QPushButton;
class QDateTimeEdit;

class AddTaskDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddTaskDialog(QWidget* parent = nullptr);
    ~AddTaskDialog() = default;  // 添加析构函数声明

    std::string getTaskName() const;
    std::string getStartTime() const;
    std::string getReminderTime() const;
    std::string getCategory() const;
    std::string getPriority() const;

private slots:
    void handleSubmit();
    void handleCancel();

private:
    QLineEdit* taskNameInput;
    QDateTimeEdit* startTimeInput;
    QDateTimeEdit* reminderTimeInput;
    QLineEdit* categoryInput;
    QLineEdit* priorityInput;
    QPushButton* submitButton;
    QPushButton* cancelButton;

    std::string taskName;
    std::string startTime;
    std::string reminderTime;
    std::string category;
    std::string priority;
};

#endif // ADDTASKDIALOG_H