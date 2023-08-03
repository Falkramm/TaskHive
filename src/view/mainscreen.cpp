#include <view/mainscreen.h>

MainScreen::MainScreen(std::shared_ptr<controller::Dispatcher> dispatcher_, QWidget *parent)
        : QMainWindow(parent), dispatcher(dispatcher_) {
    logOutAction();

    QFontDatabase::addApplicationFont(":/fonts/resources/EightBits.ttf");
    setStyleSheet(  "QWidget { "
                    "    font: 30px EightBits; "
                    "}"
                    "QLineEdit { "
                    "border-top: 2px solid #9ff; "
                    "border-left: 2px solid #9ff; "
                    "border-right: 2px solid #a886dc; "
                    "border-bottom: 2px solid #a886dc; "
                    "background-color: #f8fbfc;"
                    "}"
                    "QPushButton {"
                    "border-top: 2px solid #9ff; "
                    "border-left: 2px solid #9ff; "
                    "border-right: 2px solid #a886dc; "
                    "border-bottom: 2px solid #a886dc; "
                    "background-color: #eae4fc;"
                    "}"
                    "QPushButton:pressed {"
                    "border: 4px dashed black; "
                    "margin: -2px; "
                    "}"
                    "TaskScreen {"
                    "border: 4px dashed black; "
                    "}"
                    );
//    setMinimumSize(610, 100);

}

MainScreen::~MainScreen() {
    delete ui;
}

void MainScreen::logOutAction() {
    if (dispatcher->isAuthorized()) {
        qDebug() << "Try to logout";
        try {
            dispatcher->signOut();
        } catch (...) {//TODO need to log
            qDebug() << "Error during logout";
        }

    }
    if (!dispatcher->isAuthorized()) {
        logInScreen = new LogInScreen(this);
        connect(logInScreen, &LogInScreen::tryToLogIn, this, &MainScreen::logInAction);//TODO need disconnect?
        connect(logInScreen, &LogInScreen::tryToRegistration, this, &MainScreen::toRegistrationAction);
        setCentralWidget(logInScreen);//TODO need to disconnect all signals
    } else {
        QMessageBox::critical(this, "Error", "Can't logout");
    }
    adjustSize();
}

void MainScreen::logInAction(std::shared_ptr<Entity::User> user) {
    std::stringstream ss;
    ss << *user;
    qDebug() << "Try to authorize: " << ss.str();
    try {
        dispatcher->signIn(user);
    } catch (...) {
        QMessageBox::critical(this, "Error", "Incorrect login or password");
        qDebug() << "Incorrect login or password\n";
    }
    if (dispatcher->isAuthorized()) {
        qDebug() << "User: " << user->getLogin() << " loged\n";
        taskListScreen = new TaskListScreen(dispatcher->getTaskList(), this);
        setCentralWidget(taskListScreen);
        connect(taskListScreen, &TaskListScreen::logOut, this, &MainScreen::logOutAction);
        connect(taskListScreen, &TaskListScreen::saveAction, this, &MainScreen::saveAction);
    }
    adjustSize();
}

void MainScreen::toRegistrationAction(std::shared_ptr<Entity::User> user) {
    std::stringstream ss;
    ss << *user;
    qDebug() << "Try to registration: " << ss.str();
    try {
        dispatcher->signUp(user);
    } catch (...) {
        QMessageBox::critical(this, "Error", "Login is busy");
        qDebug() << "Login is busy\n";
    }
    adjustSize();
}

void MainScreen::saveAction(std::vector<std::shared_ptr<Entity::Task>> &tasks) {
    try{
        dispatcher->updateTasks(tasks);
    }catch(...){
        qDebug() << "Error Can't update";
    }
}

void MainScreen::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.fillRect(rect(), QColor::fromString("#e4feff"));
}
