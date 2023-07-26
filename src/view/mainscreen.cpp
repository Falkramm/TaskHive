#include <view/mainscreen.h>

MainScreen::MainScreen(std::shared_ptr<controller::Dispatcher> dispatcher_, QWidget *parent)
    : QMainWindow(parent), dispatcher(dispatcher_)
{
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
}

void MainScreen::logInAction(std::shared_ptr<Entity::User> user) {
    try {
        dispatcher->signIn(user);
        qDebug() << "User: " << user->getLogin() << " loged\n";
    } catch (...) {
        qDebug() << "Incorrect login or password\n";
    }
}
