#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QDateTimeEdit>
#include<QTcpSocket>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
};
#endif // DIALOG_H
