#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QWidget>
#include <view/view.h>
#include <QDebug>
#include <entity/User.h>
#include <QMessageBox>
class LogInScreen : public QWidget {
Q_OBJECT

public:
    explicit LogInScreen(QWidget *parent = nullptr);

    virtual ~LogInScreen();

protected:
    QLineEdit *loginInput, *passwordInput;
    QPushButton *sendButton;
    QPushButton *actionNameButton;
    QLabel *passwordRepeatLabel;
    QLineEdit *passwordRepeatInput;

    void paintEvent(QPaintEvent *event) override;

protected slots:

    virtual void PressSendButton();

    virtual void PressActionNameButton();

signals:

    void tryToLogIn(std::shared_ptr<Entity::User> user);

    void tryToRegistration(std::shared_ptr<Entity::User> user);
};

#endif // LOGINSCREEN_H
