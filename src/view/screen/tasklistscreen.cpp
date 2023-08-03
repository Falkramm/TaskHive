#include <view/screen/tasklistscreen.h>

void TaskListScreen::saveTasks() {
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

void TaskListScreen::addNewTask(std::shared_ptr<Entity::Task> task) {
    TaskScreen * newTaskScreen = new TaskScreen(task);
    tasks->push_back(newTaskScreen);
    button_container->addWidget(newTaskScreen);
    qDebug() << "Add new Task: " << tasks->size() << '\n';
}

void TaskListScreen::tryTologOut() {
    emit logOut();
}

TaskListScreen::~TaskListScreen() {
    for(size_t i = 0; i < tasks->size(); ++i)
        delete tasks->at(i);
    delete tasks;
}

TaskListScreen::TaskListScreen(const std::vector<std::shared_ptr<Entity::Task>> &tasks_, QWidget *parent) : QWidget(parent){
    tasks = new QList<TaskScreen*>();
    tasks->reserve(tasks_.size());
    button_container = new QVBoxLayout();
    for(auto task : tasks_){
        addNewTask(task);
    }

    QScrollArea* scroll_area = new QScrollArea(this);
    QWidget* scroll_widget = new QWidget(this);
    scroll_area->setWidgetResizable(scroll_widget);
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
    qDebug() << scroll_widget->styleSheet() << '\n';
    setLayout(layout);
    setMinimumHeight(800);
    setMinimumWidth(800);
    connect(addTaskButton, &QPushButton::clicked, [this](){
        addNewTask();
    });
    connect(saveTasksButton, &QPushButton::clicked, this, &TaskListScreen::saveTasks);
    connect(logOutButton, &QPushButton::clicked, this, &TaskListScreen::tryTologOut);
}

void TaskListScreen::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
}
