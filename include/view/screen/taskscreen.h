#ifndef TASKSCREEN_H
#define TASKSCREEN_H
#include <view/view.h>
#include <entity/Task.h>
#include <QDebug>
class TaskScreen : public QWidget
{
    Q_OBJECT
private:
    QDateTime toQDateTime(std::chrono::system_clock::time_point datetime){
        qint64 secsSinceEpoch = std::chrono::duration_cast<std::chrono::seconds>(datetime.time_since_epoch()).count();
        QDateTime dateTime = QDateTime::fromSecsSinceEpoch(secsSinceEpoch);
        return dateTime;
    }
public:
    explicit TaskScreen(std::shared_ptr<Entity::Task> task_, QWidget *parent = nullptr): QWidget(parent), task(task_){
        // Создание полей для ввода логина и пароля
        QLabel* titleLable = new QLabel(tr(task->getTitle().c_str()));

        QDateTime * startTime = new QDateTime(toQDateTime(task->getStartDate()));
        QDateTime * deadlineTime = new QDateTime(toQDateTime(task->getDeadlineDate()));
        QCheckBox * isCompletedBox = new QCheckBox();
        if(task->isCompleted())
            isCompletedBox->setChecked(true);
        QPushButton * unwrapButton = new QPushButton("ˇ");
        // Создание компоновщика для размещения элементов на экране
        QHBoxLayout *hLayout = new QHBoxLayout();
        hLayout->addWidget(titleLable);
        hLayout->addWidget(isCompletedBox);
        hLayout->addWidget(new QLabel(startTime->toString()));
        hLayout->addWidget(new QLabel(deadlineTime->toString()));
        hLayout->addWidget(unwrapButton);
        QVBoxLayout *vLayout = new QVBoxLayout();
        QTextEdit *descriptionEdit = new QTextEdit(tr(task->getDescription().c_str()));
        vLayout->addLayout(hLayout);
        vLayout->addWidget(descriptionEdit);
        setLayout(vLayout);
        connect(unwrapButton, &QPushButton::clicked, [descriptionEdit, unwrapButton](){
            if(descriptionEdit->isVisible()){
                unwrapButton->setText("ˇ");
                    descriptionEdit->setVisible(false);
            } else{
                    unwrapButton->setText("^");
                    descriptionEdit->setVisible(true);
            }
        });
        //connect(sendButton, &QPushButton::clicked, this, &LogInScreen::PressSendButton);
    }
    virtual ~TaskScreen(){
        delete taskDescriptionWidget;
    }
protected:
    std::shared_ptr<Entity::Task> task;
    QWidget * taskDescriptionWidget;
signals:
protected slots:
};
#endif // TASKSCREEN_H
