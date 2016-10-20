#ifndef TCPSOCKSERVER_H
#define TCPSOCKSERVER_H

#include <QtNetwork>
#include <QtGui>
#include <QTcpServer>
#include <QStringList>
#include <qdebug.h>

class TcpSockServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpSockServer(QObject *parent = 0);

protected:
    void incomingConnection(int socketDescriptor);

public slots:

};

#endif // TCPSOCKSERVER_H
