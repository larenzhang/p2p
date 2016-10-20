#ifndef TCPCONTHREAD_H
#define TCPCONTHREAD_H

#include <QThread>
#include <QtNetwork>
#include <QtGui>
#include <QTcpSocket>
#include "sqlitedb.h"
#include <qdebug.h>

class TcpConThread : public QThread
{
    Q_OBJECT
public:
    TcpConThread(int socketDescriptor, QObject *parent);
    void run();

private:
    int socketDescriptor;
    QTcpSocket *tcpSocket;
    SqliteDB *db;

signals:
    void error(QTcpSocket::SocketError socketError);

public slots:
    void on_Ready_Read();

};

#endif // TCPCONTHREAD_H
