#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QWidget>
#include <view/view.h>
#include <QDebug>
#include <entity/User.h>

class LogInScreen : public QWidget
{
    Q_OBJECT
public:
    explicit LogInScreen(QWidget *parent = nullptr);
    virtual ~LogInScreen();
protected:
    QLineEdit *loginInput, *passwordInput;
    QPushButton *sendButton;
signals:
protected slots:
    virtual void PressSendButton(){
        qDebug() << "Signed: Login: " << loginInput->text() << " Password: " << passwordInput->text() << '\n';
        emit tryToLogIn(std::make_shared<Entity::User>(loginInput->text().toStdString(), passwordInput->text().toStdString()));
    }
signals:
    void tryToLogIn(std::shared_ptr<Entity::User> user);
};

#endif // LOGINSCREEN_H
