#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QLabel>
#include<QPushButton>

class timeserver;
class dialog : public QDialog
{
    Q_OBJECT
public:
    explicit dialog(QDialog *parent = nullptr);


signals:
public slots:
    void slotShow();//用于界面上显示请求的次数

private:
    QLabel *Label;//显示监听端口
    QLabel *Label2;//显示请求此时
    QPushButton *quitBtn;

    timeserver *timeServer;
    int count;
};

#endif // DIALOG_H
