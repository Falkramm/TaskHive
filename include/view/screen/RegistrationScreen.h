#ifndef REGISTRATIONSCREEN_H
#define REGISTRATIONSCREEN_H
#include <view/screen/loginscreen.h>

class RegistrationScreen : public LogInScreen
{
    Q_OBJECT
public:
    explicit RegistrationScreen(QWidget *parent = nullptr): LogInScreen(parent){
        QLabel* passwordRepeatLabele = new QLabel(tr("Повторите пароль: "));
        passwordRepeatInput = new QLineEdit();
        passwordRepeatInput->setEchoMode(QLineEdit::Password); // Скрытие символов пароля
        layout()->removeWidget(sendButton);
        layout()->addWidget(passwordRepeatLabele);
        layout()->addWidget(passwordRepeatInput);
        layout()->addWidget(sendButton);
    }
    virtual ~RegistrationScreen(){
        delete passwordRepeatInput;
    }
private:
    QLineEdit *passwordRepeatInput;
signals:
protected slots:
    void PressSendButton() override{
        if(passwordRepeatInput->isVisible())
        passwordRepeatInput->setVisible(false);
        else
        passwordRepeatInput->setVisible(true);
        qDebug() << "Signed: Login: " << loginInput->text() << " Password: " << passwordInput->text() << " Repeate: " << passwordRepeatInput->text() << '\n';
    }
};
#endif // REGISTRATIONSCREEN_H
