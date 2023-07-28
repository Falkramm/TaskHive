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
    std::chrono::system_clock::time_point toTimePoint(QDateTime *dateTime) {
        return std::chrono::system_clock::from_time_t(dateTime->toSecsSinceEpoch());
    }
private:
    QLineEdit* titleEdit;
    QDateTime * startTime;
    QDateTime * deadlineTime;
    QCheckBox * isCompletedBox;
    QTextEdit *descriptionEdit;
public:
    explicit TaskScreen(std::shared_ptr<Entity::Task> task_, QWidget *parent = nullptr): QWidget(parent), task(task_){
        // Создание полей для ввода логина и пароля
        titleEdit = new QLineEdit(tr(task->getTitle().c_str()));
        startTime = new QDateTime(toQDateTime(task->getStartDate()));
        deadlineTime = new QDateTime(toQDateTime(task->getDeadlineDate()));
        isCompletedBox = new QCheckBox("Completed");
        if(task->isCompleted())
            isCompletedBox->setChecked(true);
        QPushButton * unwrapButton = new QPushButton("ˇ");
        // Создание компоновщика для размещения элементов на экране
        QHBoxLayout *hLayout = new QHBoxLayout();
        hLayout->addWidget(titleEdit);
        hLayout->addWidget(isCompletedBox);
        hLayout->addWidget(new QLabel(startTime->toString()));
        hLayout->addWidget(new QLabel(deadlineTime->toString()));
        hLayout->addWidget(unwrapButton);
        QVBoxLayout *vLayout = new QVBoxLayout();
        descriptionEdit = new QTextEdit(tr(task->getDescription().c_str()));
        descriptionEdit->setVisible(false);
        vLayout->addLayout(hLayout);
        vLayout->addWidget(descriptionEdit);
        setLayout(vLayout);
        connect(unwrapButton, &QPushButton::clicked, [this, unwrapButton](){
            if(descriptionEdit->isVisible()){
                unwrapButton->setText("ˇ");
                    descriptionEdit->setVisible(false);
            } else{
                    unwrapButton->setText("^");
                    descriptionEdit->setVisible(true);
            }
        });
    }
    virtual ~TaskScreen(){
    }

    std::shared_ptr<Entity::Task> getTask() {
        //titleEdit;
        //    QDateTime * startTime;
        //    QDateTime * deadlineTime;
        //    QCheckBox * isCompletedBox;
        //    QTextEdit *descriptionEdit;
        task->setStartDate(toTimePoint(startTime));
        task->setDeadlineDate(toTimePoint(deadlineTime));
        task->setCompleted(isCompletedBox->isChecked());
        task->setTitle(titleEdit->text().toStdString());
        task->setDescription(descriptionEdit->toPlainText().toStdString());
        return task;
    }

protected:
    std::shared_ptr<Entity::Task> task;
signals:
protected slots:
};
#endif // TASKSCREEN_H
