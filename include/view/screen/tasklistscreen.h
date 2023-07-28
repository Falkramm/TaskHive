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
        button_container = new QVBoxLayout();
        for(auto task : tasks_){
            addNewTask(task);
        }
        QScrollArea* scroll_area = new QScrollArea;
        scroll_area->setWidgetResizable(true);
        QWidget* scroll_widget = new QWidget;
        scroll_widget->setLayout(button_container);
        scroll_area->setWidget(scroll_widget);
        QVBoxLayout * layout = new QVBoxLayout();
        QPushButton * addTaskButton = new QPushButton("Add");
        QPushButton * saveTasksButton = new QPushButton("Save");
        QPushButton * logOutButton = new QPushButton("LogOut");
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(addTaskButton);
        buttonLayout->addWidget(saveTasksButton);
        buttonLayout->addWidget(logOutButton);
        layout->addLayout(buttonLayout);
        layout->addWidget(scroll_area);
        setLayout(layout);
        setMinimumHeight(800);
        setMinimumWidth(800);
        connect(addTaskButton, &QPushButton::clicked, [this](){
            addNewTask();
        });
        connect(saveTasksButton, &QPushButton::clicked, this, &TaskListScreen::saveTasks);
        connect(logOutButton, &QPushButton::clicked, this, &TaskListScreen::tryTologOut);
    }
    virtual ~TaskListScreen(){
        for(size_t i = 0; i < tasks->size(); ++i)
            delete tasks->at(i);
        delete tasks;
    }
public slots:
    void tryTologOut(){
        emit logOut();
    };
    void addNewTask(std::shared_ptr<Entity::Task> task = std::make_shared<Entity::Task>("","","","")){
        TaskScreen * newTaskScreen = new TaskScreen(task, this);
        tasks->push_back(newTaskScreen);
        button_container->addWidget(newTaskScreen);
        qDebug() << "Add new Task: " << tasks->size() << '\n';
    };
    void saveTasks(){
        qDebug() << "Try to save";
        std::vector<std::shared_ptr<Entity::Task> > taskList;
        taskList.reserve(tasks->size());
        for(auto taskScreen : *tasks){
            std::shared_ptr<Entity::Task> task = taskScreen->getTask();
            taskList.push_back(task);
        }
        emit saveAction(taskList);
        for(auto task : taskList)
            std::cout << *task << '\n';
    }
protected:
    QVBoxLayout *button_container;
    QList<TaskScreen *> *tasks;
signals:
    void logOut();
    void saveAction(std::vector<std::shared_ptr<Entity::Task> > &tasks);
protected slots:
};
#endif // TASKLISTSCREEN_H
