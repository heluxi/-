#include "timeserver.h"
#include"timethread.h"
#include"dialog.h"

timeserver::timeserver(QObject *parent)
    : QTcpServer{parent}
{
    dlg=(dialog*)parent;
}
//每当客户端请求到达时，服务器将启动一个新线程为它返回当前的时间，服务完毕后，这个线程将自动退出

void timeserver::incomingConnection(qintptr socketDecriptor)
{
    timeThread *thread=new timeThread(socketDecriptor,0);//创建一个线程
    connect(thread,&timeThread::finished,dlg,&dialog::slotShow);
    connect(thread,&timeThread::finished,thread,&timeThread::deleteLater,Qt::DirectConnection);
    thread->start();
}
