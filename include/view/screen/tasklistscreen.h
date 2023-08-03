#ifndef TASKLISTSCREEN_H
#define TASKLISTSCREEN_H
#include <view/view.h>
#include <view/screen/taskscreen.h>
#include <QDebug>
class TaskListScreen : public QWidget
{
    Q_OBJECT

public:
    explicit TaskListScreen(const std::vector<std::shared_ptr<Entity::Task>> &tasks_, QWidget *parent = nullptr);
    virtual ~TaskListScreen();
public slots:
    void tryTologOut();;
    void addNewTask(std::shared_ptr<Entity::Task> task = std::make_shared<Entity::Task>("","","",""));;
    void saveTasks();
protected:
    QVBoxLayout *button_container;
    QList<TaskScreen *> *tasks;
signals:
    void logOut();
    void saveAction(std::vector<std::shared_ptr<Entity::Task> > &tasks);
protected slots:

    void paintEvent(QPaintEvent *event) override;
};
#endif // TASKLISTSCREEN_H
