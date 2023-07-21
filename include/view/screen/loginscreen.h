#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QWidget>
#include <view/view.h>
#include <QDebug>
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
    }
};

#endif // LOGINSCREEN_H
