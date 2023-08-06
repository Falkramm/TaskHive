#include <view/screen/tasklistscreen.h>

void TaskListScreen::saveTasks() {
    qDebug() << "Try to save";
    std::vector<std::shared_ptr<Entity::Task> > taskList;
    taskList.reserve(tasks->size());
    for (auto taskScreen: *tasks) {
        std::shared_ptr<Entity::Task> task = taskScreen->first->getTask();
        taskList.push_back(task);
    }
    emit saveAction(taskList);
    for (auto task: taskList)
        std::cout << *task << '\n';
}

void TaskListScreen::addNewTask(std::shared_ptr<Entity::Task> task) {
    auto pair = new QPair<TaskScreen*, QFrame*>();
    if(!tasks->empty()){
        QFrame *line = new QFrame(this);
        line->setFrameShape(QFrame::HLine); // Horizontal line
        line->setFrameShadow(QFrame::Sunken);
        line->setLineWidth(1);
        button_container->addWidget(line);
        pair->second = line;
    }
    TaskScreen *newTaskScreen = new TaskScreen(task);
    pair->first = newTaskScreen;
    button_container->addWidget(newTaskScreen);
    //TODO need to remove lines
    tasks->push_back(pair);
    qDebug() << "Add new Task: " << tasks->size() << '\n';
}

void TaskListScreen::tryTologOut() {
    emit logOut();
}

TaskListScreen::~TaskListScreen() {
    for (size_t i = 0; i < tasks->size(); ++i)
        delete tasks->at(i);
    delete tasks;
}

TaskListScreen::TaskListScreen(const std::vector<std::shared_ptr<Entity::Task>> &tasks_, QWidget *parent) : QWidget(
        parent) {
    tasks = new QList<QPair<TaskScreen *, QFrame *> *>();
    tasks->reserve(tasks_.size());
    button_container = new QVBoxLayout();
    button_container->setSpacing(0);
    for (auto task: tasks_) {
        addNewTask(task);
    }

    QScrollArea *scroll_area = new QScrollArea(this);
    scroll_area->setStyleSheet("QWidget { "
                               "    font: 30px EightBits; "
                               "    background-color: #e4feff;"
                               "}"
                               "QLineEdit { "
                               "    border-top: 2px solid #9ff; "
                               "    border-left: 2px solid #9ff; "
                               "    border-right: 2px solid #a886dc; "
                               "    border-bottom: 2px solid #a886dc; "
                               "    background-color: #f8fbfc;"
                               "}"
                               "QPushButton {"
                               "    border-top: 2px solid #9ff; "
                               "    border-left: 2px solid #9ff; "
                               "    border-right: 2px solid #a886dc; "
                               "    border-bottom: 2px solid #a886dc; "
                               "    background-color: #eae4fc;"
                               "}"
                               "QPushButton:pressed {"
                               "    border: 4px dashed black; "
                               "    margin: -2px; "
                               "}"
                               "QVBoxLayout > QWidget:not(QLayoutItem) {"
                               "    border-bottom: 2px solid black;"
                               "    height: 2px;"
                               "}");
    QWidget *scroll_widget = new QWidget(scroll_area);
    scroll_area->setWidgetResizable(scroll_widget);
    scroll_widget->setLayout(button_container);
    scroll_area->setWidget(scroll_widget);
    QVBoxLayout *layout = new QVBoxLayout();
    QPushButton *addTaskButton = new QPushButton("Add");
    QPushButton *saveTasksButton = new QPushButton("Save");
    QPushButton *logOutButton = new QPushButton("LogOut");
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
    connect(addTaskButton, &QPushButton::clicked, [this]() {
        addNewTask();
    });
    connect(saveTasksButton, &QPushButton::clicked, this, &TaskListScreen::saveTasks);
    connect(logOutButton, &QPushButton::clicked, this, &TaskListScreen::tryTologOut);
}

void TaskListScreen::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
}
