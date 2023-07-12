#ifndef TIMETHREAD_H
#define TIMETHREAD_H

#include <QThread>
#include<QTcpSocket>

class timeThread : public QThread
{
    Q_OBJECT
public:
    explicit timeThread(qintptr socketDescriptor,QThread *parent = nullptr);
    void run();
signals:
    void error(QTcpSocket::SocketError socketError);//出错信号
private:
    qintptr socketDescriper;//套接字描述符
};

#endif // TIMETHREAD_H
