#ifndef TIMESERVER_H
#define TIMESERVER_H

#include <QObject>
#include<QTcpServer>
class dialog;

class timeserver : public QTcpServer
{
    Q_OBJECT
public:
    explicit timeserver(QObject *parent = nullptr);

signals:
protected:
    void incomingConnection(qintptr socketDecriptor);//服务器端有新连接时被调用 其参数为所接受新连接的套接字的描述符
private:
    dialog *dlg;

};

#endif // TIMESERVER_H
