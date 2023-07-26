//#ifndef MAINSCREEN_H
//#define MAINSCREEN_H
//
//#include <QMainWindow>
//#include <controller/dispatcher/dispatcher.h>
//#include <view/view.h>
//#include <view/screen/loginscreen.h>
//
//QT_BEGIN_NAMESPACE
//namespace Ui { class MainScreen; }
//QT_END_NAMESPACE
//
//class MainScreen : public QMainWindow {
//Q_OBJECT
//
//private:
//    std::shared_ptr<controller::Dispatcher> dispatcher;
//public:
//    MainScreen(std::shared_ptr<controller::Dispatcher> dispatcher_ = std::make_shared<controller::Dispatcher>(), QWidget *parent = nullptr);
//
//    ~MainScreen();
//
//public slots:
//
//    void logOutAction() {
//        try {
//            dispatcher->signOut();
//        } catch (...) {//TODO need to log
//        }
//        LogInScreen *logInScreen = new LogInScreen(this);
//        setCentralWidget(logInScreen);//TODO need to disconnect all signals
//    }
//
//    void logInAction(std::shared_ptr<Entity::User> user) {
//        try {
//            dispatcher->signIn(user);
//            qDebug() << "User: " << user->getLogin() << " loged\n";
//        } catch (...) {
//            qDebug() << "Incorrect login or password\n";
//        }
//    }
//
//private:
//    Ui::MainScreen *ui;
//};
//
//
//#endif // MAINSCREEN_H
