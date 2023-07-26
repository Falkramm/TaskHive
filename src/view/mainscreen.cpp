#include <view/mainscreen.h>
#include <sstream>
MainScreen::MainScreen(std::shared_ptr<controller::Dispatcher> dispatcher_, QWidget *parent)
    : QMainWindow(parent), dispatcher(dispatcher_)
{
    logOutAction();
}

MainScreen::~MainScreen()
{
    delete ui;
}

void MainScreen::logOutAction() {
    try {
        dispatcher->signOut();
    } catch (...) {//TODO need to log
    }
    LogInScreen *logInScreen = new LogInScreen(this);
    setCentralWidget(logInScreen);//TODO need to disconnect all signals
    connect(logInScreen, &LogInScreen::tryToLogIn, this, &MainScreen::logInAction);//TODO need disconnect?
}

void MainScreen::logInAction(std::shared_ptr<Entity::User> user) {
    std::stringstream ss;
    ss << *user;
    qDebug() << "Try to authorize: " << ss.str();
    try {
        dispatcher->signIn(user);
    } catch (...) {
        qDebug() << "Incorrect login or password\n";
    }
    if(dispatcher->isAuthorized()) {
        qDebug() << "User: " << user->getLogin() << " loged\n";
        TaskListScreen *taskListScreen = new TaskListScreen(dispatcher->getTaskList(), this);
        setCentralWidget(taskListScreen);
    }
}
