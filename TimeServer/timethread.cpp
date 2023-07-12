#include "timethread.h"
#include<QDataStream>
#include<QDateTime>

timeThread::timeThread(qintptr socketDescriptor,QThread *parent)
    : QThread{parent},socketDescriper{socketDescriptor}
{

}

void timeThread::run()
{
    QTcpSocket tcpSocket;
    if(!tcpSocket.setSocketDescriptor(socketDescriper))
    {
        emit error(tcpSocket.error());
        return;
    }
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    uint time2u=QDateTime::currentDateTime().toTime_t();
    tcpSocket.write(block);//将获取的时间传回客户端
    tcpSocket.disconnectFromHost();    //断开连接
    tcpSocket.waitForDisconnected();
}
