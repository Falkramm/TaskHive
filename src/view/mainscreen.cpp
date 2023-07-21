#include <view/mainscreen.h>

MainScreen::MainScreen(QWidget *parent)
    : QMainWindow(parent)
{
}

MainScreen::~MainScreen()
{
    delete ui;
}
