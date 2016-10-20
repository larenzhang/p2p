#include "tcpconthread.h"
#include "mainwindow.h"

TcpConThread::TcpConThread(int socketDescriptor, QObject *parent) :
    QThread(parent),socketDescriptor(socketDescriptor)
{

}

void TcpConThread::run()
{
    tcpSocket=new QTcpSocket;
    qDebug()<<"tcpconthead 13";
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(on_Ready_Read()));
    if(!tcpSocket->setSocketDescriptor(socketDescriptor))
    {
        emit error(tcpSocket->error());
        return;
    }
    exec();
}

void TcpConThread::on_Ready_Read()
{
    /*
    QString strLogin=tcpSocket->readAll();
    QStringList strListUser=strLogin.split("|");
    QString id=strListUser.at(0);
    QString password=strListUser.at(1);
    */

    qDebug()<<"tcpconthead 32";
    db=new SqliteDB;

    QString ip=tcpSocket->peerAddress().toString();
    int port=tcpSocket->peerPort();

    qDebug()<<"ip"<<tcpSocket->peerAddress().toString();
    qDebug()<<"port"<<tcpSocket->peerPort()<<port;

    QByteArray block =tcpSocket->readAll();
    QDataStream in(&block,QIODevice::ReadOnly);
    quint16 dataGramSize;
    QString msgType;
    in>>dataGramSize>>msgType;

    if("MSG_CLIENT_USER_REGISTER"==msgType)
    {
        QString id;
        QString password;
        QString name;

        qDebug()<<"tcpconthead 52";

        in>>id>>password>>name;

        if(0==db->insertNewUser(id,password,name,ip,QString::number(port)))
        {
            qDebug()<<"register failed!";
            QString msgType="MSG_ID_ALREADY_EXIST";
            QByteArray block;
            QDataStream out(&block,QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_4_6);
            out<<(quint16)0<<msgType;
            out.device()->seek(0);
            out<<(quint16)(block.size()-sizeof(quint16));
            tcpSocket->write(block);
        }
        else
        {
            qDebug()<<"register success!";
            QByteArray block;
            QDataStream out(&block,QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_4_6);
            QString msgType="MSG_CLIENT_REGISTER_SUCCESS";
            out<<(quint16)0<<msgType;
            out.device()->seek(0);
            out<<(quint16)(block.size()-sizeof(quint16));
            tcpSocket->write(block);
        }
    }
    else if("MSG_USER_LOGIN"==msgType)
    {

        QString id;
        QString password;
        in>>id>>password;
        db->getUserInfo(id);

        if(db->strListUser.isEmpty())
        {
            QByteArray block;
            QDataStream out(&block,QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_4_6);
            QString msgType="MSG_ID_NOTEXIST";
            out<<(quint16)0<<msgType;
            out.device()->seek(0);
            out<<(quint16)(block.size()-sizeof(quint16));
            tcpSocket->write(block);
        }
        else if(db->strListUser.at(1)!=password)
        {
            QByteArray block;
            QDataStream out(&block,QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_4_6);
            QString msgType="MSG_PWD_ERROR";
            out<<(quint16)0<<msgType;
            out.device()->seek(0);
            out<<(quint16)(block.size()-sizeof(quint16));
            tcpSocket->write(block);
        }
        else if(db->strListUser.at(1)==password)
        {

            if(db->strListUser.at(3)=="1")
            {
                QByteArray block;
                QDataStream out(&block,QIODevice::WriteOnly);
                out.setVersion(QDataStream::Qt_4_6);
                QString msgType="MSG_LOGIN_ALREADY";
                out<<(quint16)0<<msgType;
                out.device()->seek(0);
                out<<(quint16)(block.size()-sizeof(quint16));
                tcpSocket->write(block);
            }
            else
            {
                QByteArray block;
                QDataStream out(&block,QIODevice::WriteOnly);
                out.setVersion(QDataStream::Qt_4_6);
                QString msgType="MSG_LOGIN_SUCCESS";
                out<<(quint16)0<<msgType;
                out.device()->seek(0);
                out<<(quint16)(block.size()-sizeof(quint16));
                tcpSocket->write(block);
                db->updateUserLogStat(id,"1");
                db->updateUserIp(id,tcpSocket->peerAddress().toString());
            }

            QString msgType="MSG_SYSTEM_UPDATE_LOGSTAT";
            QByteArray block;
            QDataStream out(&block,QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_4_6);
            QString endMsg="END";
            out<<(quint16)0<<msgType<<id<<endMsg;
            out.device()->seek(0);
            out<<(quint16)(block.size()-sizeof(quint16));


            QUdpSocket *udpSocket=new QUdpSocket(this);
            if(!udpSocket->writeDatagram(block.data(),block.size(),QHostAddress(ip),port+1))
            {
                QMessageBox::critical(NULL,tr("提示"),tr("服务器内部通信错误"));
            }
        }
    }
}
