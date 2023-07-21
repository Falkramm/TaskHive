#ifndef TASKLISTSCREEN_H
#define TASKLISTSCREEN_H
#include <view/view.h>
#include <view/screen/taskscreen.h>
#include <QDebug>
class TaskListScreen : public QWidget
{
    Q_OBJECT
public:
    explicit TaskListScreen(const std::vector<std::shared_ptr<Entity::Task>> &tasks_, QWidget *parent = nullptr): QWidget(parent){
        tasks = new QList<TaskScreen*>();
        tasks->reserve(tasks_.size());
        QVBoxLayout *button_container = new QVBoxLayout();

        for(auto task : tasks_){
            TaskScreen *screen = new TaskScreen(task, this);
            tasks->push_back(screen);
            button_container->addWidget(screen);
        }
        QScrollArea* scroll_area = new QScrollArea;
        scroll_area->setWidgetResizable(true);
        QWidget* scroll_widget = new QWidget;
        scroll_widget->setLayout(button_container);
        scroll_area->setWidget(scroll_widget);
        QVBoxLayout * layout = new QVBoxLayout();
        layout->addWidget(scroll_area);
        setLayout(layout);
        setMinimumHeight(800);
        setMinimumWidth(800);
    }
    virtual ~TaskListScreen(){
        delete tasks;
    }
protected:
    QList<TaskScreen *> *tasks;
signals:
protected slots:
};
#endif // TASKLISTSCREEN_H
