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
signals:
protected slots:

    virtual void PressSendButton() {
        if (passwordRepeatLabel->isVisible()) {
            if(passwordInput->text() == passwordRepeatInput->text())
                emit tryToRegistration(std::make_shared<Entity::User>(loginInput->text().toStdString(),passwordInput->text().toStdString()));
            else{
                QMessageBox::critical(this, "Error", "Passwords don't match");
            }
        } else {
            emit tryToLogIn(std::make_shared<Entity::User>(loginInput->text().toStdString(),passwordInput->text().toStdString()));
        }
    }

    virtual void PressActionNameButton() {
        if (passwordRepeatLabel->isVisible()) {
            actionNameButton->setText("SignIn");
            passwordRepeatLabel->setVisible(false);
            passwordRepeatInput->setVisible(false);
        } else {
            actionNameButton->setText("SignUp");
            passwordRepeatLabel->setVisible(true);
            passwordRepeatInput->setVisible(true);
        }
    }

signals:

    void tryToLogIn(std::shared_ptr<Entity::User> user);

    void tryToRegistration(std::shared_ptr<Entity::User> user);
};

#endif // LOGINSCREEN_H
