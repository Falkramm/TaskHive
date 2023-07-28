#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>
#include <controller/dispatcher/dispatcher.h>
#include <view/view.h>
#include <view/screen/loginscreen.h>
#include <view/screen/tasklistscreen.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainScreen; }
QT_END_NAMESPACE

class MainScreen : public QMainWindow {
Q_OBJECT

private:
    std::shared_ptr<controller::Dispatcher> dispatcher;
public:
    MainScreen(std::shared_ptr<controller::Dispatcher> dispatcher_ = std::make_shared<controller::Dispatcher>(), QWidget *parent = nullptr);

    ~MainScreen();

public slots:

    void logOutAction();

    void logInAction(std::shared_ptr<Entity::User> user);

    void toRegistrationAction(std::shared_ptr<Entity::User> user);

private:
    Ui::MainScreen *ui;
};


#endif // MAINSCREEN_H
