#include <view/mainscreen.h>
#include <sstream>

MainScreen::MainScreen(std::shared_ptr<controller::Dispatcher> dispatcher_, QWidget *parent)
        : QMainWindow(parent), dispatcher(dispatcher_) {
    logOutAction();
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
    }
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

}
