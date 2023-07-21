#include <view/screen/loginscreen.h>
LogInScreen::LogInScreen(QWidget *parent)
    : QWidget{parent}
{
    // Создание полей для ввода логина и пароля
    QLabel* usernameLabel = new QLabel(tr("Логин: "));
    loginInput = new QLineEdit();
    QLabel* passwordLabel = new QLabel(tr("Пароль: "));
    passwordInput = new QLineEdit();
    passwordInput->setEchoMode(QLineEdit::Password); // Скрытие символов пароля

    // Создание кнопки входа
    sendButton = new QPushButton(tr("Войти"));

    // Создание компоновщика для размещения элементов на экране
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(usernameLabel);
    layout->addWidget(loginInput);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordInput);
    layout->addWidget(sendButton);
    setLayout(layout);
    connect(sendButton, &QPushButton::clicked, this, &LogInScreen::PressSendButton);
}

LogInScreen::~LogInScreen(){
    delete loginInput;
    delete passwordInput;
    delete sendButton;
}
