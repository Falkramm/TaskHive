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
    passwordRepeatLabel = new QLabel("Repeat password: ");
    passwordRepeatInput = new QLineEdit();
    passwordRepeatLabel->setVisible(false);
    passwordRepeatInput->setVisible(false);
    passwordRepeatInput->setEchoMode(QLineEdit::Password);
    // Создание кнопки входа
    sendButton = new QPushButton(tr("Send"));
    actionNameButton = new QPushButton(tr("SignIn"));

    // Создание компоновщика для размещения элементов на экране
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(actionNameButton);
    layout->addWidget(usernameLabel);
    layout->addWidget(loginInput);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordInput);
    layout->addWidget(passwordRepeatLabel);
    layout->addWidget(passwordRepeatInput);
    layout->addWidget(sendButton);
    setLayout(layout);
    connect(sendButton, &QPushButton::clicked, this, &LogInScreen::PressSendButton);
    connect(actionNameButton, &QPushButton::clicked, this, &LogInScreen::PressActionNameButton);
}

LogInScreen::~LogInScreen(){
    delete loginInput;
    delete passwordInput;
    delete sendButton;
}
