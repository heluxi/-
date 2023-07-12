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
public slots:
    void enableGetBtn();
    void getTime();
    void readTime();
    void showError(QAbstractSocket::SocketError socketError);
public:
    QLabel *serverNameLabel;
    QLineEdit *serverNameLineEdit;
    QLabel *portLabel;
    QLineEdit *portLineEdit;
    QLabel *stateLabel;
    QPushButton *getBtn;
    QPushButton *quiBtn;
    QDateTimeEdit *dateTimeEdit;
    uint time2u;
    QTcpSocket *tcpSoket;
};
#endif // DIALOG_H
