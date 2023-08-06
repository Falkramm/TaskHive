#ifndef TASKSCREEN_H
#define TASKSCREEN_H
#include <view/view.h>
#include <entity/Task.h>
#include <QDebug>
class TaskScreen : public QWidget
{
    Q_OBJECT
private:
    QDateTime toQDateTime(std::chrono::system_clock::time_point datetime);
    std::chrono::system_clock::time_point toTimePoint(QDateTime *dateTime);
private:
    QLineEdit* titleEdit;
    QDateTime * startTime;
    QDateTime * deadlineTime;
    QCheckBox * isCompletedBox;
    QTextEdit *descriptionEdit;
public:
    explicit TaskScreen(std::shared_ptr<Entity::Task> task_, QWidget *parent = nullptr);
    virtual ~TaskScreen() = default;

    std::shared_ptr<Entity::Task> getTask();

protected:
    std::shared_ptr<Entity::Task> task;
signals:
protected slots:
};
#endif // TASKSCREEN_H
