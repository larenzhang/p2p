#include "tcpsockserver.h"
#include "tcpconthread.h"

TcpSockServer::TcpSockServer(QObject *parent) :
    QTcpServer(parent)
{
}

void TcpSockServer::incomingConnection(int socketDescriptor)
{
    qDebug()<<"hhhhhhh"<<socketDescriptor;
    TcpConThread *thread=new TcpConThread(socketDescriptor,this);
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
    thread->start();
}
