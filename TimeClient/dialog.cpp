#include "dialog.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QGridLayout>
#include<QDataStream>
#include<QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("多线程时间服务客户端"));
    serverNameLabel =new QLabel(tr("服务器名"));
    serverNameLineEdit=new QLineEdit("Localhost");
    portLabel=new QLabel(tr("端口："));
    portLineEdit=new QLineEdit;
    QGridLayout *layout=new QGridLayout();
    layout->addWidget(serverNameLabel,0,0);//第1行第一列
    layout->addWidget(serverNameLineEdit,0,1);//第1行第一列
    layout->addWidget(portLabel,1,0);
    layout->addWidget(portLineEdit,1,1);

    dateTimeEdit=new QDateTimeEdit(this);
    QHBoxLayout *layout1=new QHBoxLayout;
    layout1->addWidget(dateTimeEdit);

    stateLabel=new QLabel(tr("请先运行时间服务器"));
    QHBoxLayout *layout2=new QHBoxLayout;
    layout2->addWidget(stateLabel);

    getBtn=new QPushButton(tr("获取时间"));
    getBtn->setDefault(true);
    getBtn->setEnabled(false);
    quiBtn=new QPushButton(tr("退出"));
    QHBoxLayout *layout3=new QHBoxLayout;
    layout3->addStretch();
    layout3->addWidget(getBtn);
    layout3->addWidget(quiBtn);

    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    mainLayout->addLayout(layout);
    mainLayout->addLayout(layout1);
    mainLayout->addLayout(layout2);
    mainLayout->addLayout(layout3);

    connect(serverNameLineEdit,&QLineEdit::textChanged,this,&Dialog::enableGetBtn);
    connect(portLineEdit,&QLineEdit::textChanged,this,&Dialog::enableGetBtn);
    connect(getBtn,&QPushButton::clicked,this,&Dialog::getTime);
    connect(quiBtn,&QPushButton::clicked,this,&Dialog::close);

    tcpSoket=new QTcpSocket(this);
    connect(tcpSoket,&QTcpSocket::readyRead,this,&Dialog::readTime);
    //connect(tcpSoket,&QTcpSocket::error,this,&Dialog::showError);
    portLineEdit->setFocus();

}

Dialog::~Dialog()
{
}

void Dialog::enableGetBtn()
{
    getBtn->setEnabled(!serverNameLineEdit->text().isEmpty()&&!portLineEdit->text().isEmpty());
}

void Dialog::getTime()
{
    getBtn->setEnabled(false);
    time2u=0;
    tcpSoket->abort();
    tcpSoket->connectToHost(serverNameLineEdit->text(),portLineEdit->text().toInt());

}

void Dialog::readTime()
{
    QDataStream in(tcpSoket);
    in.setVersion(QDataStream::Qt_5_9);
    if(time2u==0)
    {
        if(tcpSoket->bytesAvailable()<(int)sizeof(uint))
            return;
        in>>time2u;
    }
    dateTimeEdit->setDateTime(QDateTime::fromTime_t(time2u));
    getBtn->setEnabled(true);
}

void Dialog::showError(QAbstractSocket::SocketError socketError)
{

    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this,tr("时间服务客户端"),tr("主机不可达"));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this,tr("时间服务客户端"),tr("连接被拒绝"));
        break;
    default:
        QMessageBox::information(this,tr("时间服务客户端"),tr("产生的错误：%1").arg(tcpSoket->errorString()));
        break;
    }
    getBtn->setEnabled(false);
}

