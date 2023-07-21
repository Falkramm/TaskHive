#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>
#include <view/view.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainScreen; }
QT_END_NAMESPACE

class MainScreen : public QMainWindow
{
    Q_OBJECT

public:
    MainScreen(QWidget *parent = nullptr);
    ~MainScreen();

private:
    Ui::MainScreen *ui;
};


#endif // MAINSCREEN_H
