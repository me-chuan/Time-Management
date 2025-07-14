#ifndef EDITTASKDIALOG_H
#define EDITTASKDIALOG_H

#include <QDialog>
#include <string>
#include "Task.h"

class QLineEdit;
class QPushButton;
class QDateTimeEdit;
class QCheckBox;

class EditTaskDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditTaskDialog(const Task& task, QWidget* parent = nullptr);

    std::string getTaskName() const;
    std::string getStartTime() const;
    std::string getReminderTime() const;
    std::string getCategory() const;
    std::string getPriority() const;
    bool getIsDone() const;

private slots:
    void handleSubmit();
    void handleCancel();

private:
    QLineEdit* taskNameInput;
    QDateTimeEdit* startTimeInput;
    QDateTimeEdit* reminderTimeInput;
    QLineEdit* categoryInput;
    QLineEdit* priorityInput;
    QCheckBox* doneCheckBox;
    QPushButton* submitButton;
    QPushButton* cancelButton;

    std::string taskName;
    std::string startTime;
    std::string reminderTime;
    std::string category;
    std::string priority;
    bool isDone;
};

#endif // EDITTASKDIALOG_H
