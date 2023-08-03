#include <view/screen/loginscreen.h>
LogInScreen::LogInScreen(QWidget *parent)
    : QWidget{parent}
{
    setMinimumSize(610, 100);
    qDebug() << parentWidget()->font().family().toStdString() << '\n';
    // Создание полей для ввода логина и пароля
    QLabel* usernameLabel = new QLabel(tr("Login: "));
    loginInput = new QLineEdit();
    QLabel* passwordLabel = new QLabel(tr("Password: "));
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

void LogInScreen::PressSendButton() {
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

void LogInScreen::PressActionNameButton() {
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

void LogInScreen::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
}

