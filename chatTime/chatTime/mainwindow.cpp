#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QUdpSocket>
#include <QHostAddress>
#include <QListWidget>
#include <QDebug.h>

MainWindow::MainWindow(QString id, QString ip, QString port, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->ip=ip;
    this->id=id;
    this->port=port;
    this->init();
    ui->setupUi(this);
    qDebug()<<"fffff"<<ip<<id<<port;

    bool flag =  connect(ui->userListWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(userListWidget_itemDoubleClicked(QListWidgetItem*)));
    qDebug("the flag is %d",flag);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::init()
{
    udpSocket=new QUdpSocket(this);
    udpSocket->bind(6666);
    QString msgType="MSG_CLIENT_NEW_CONN";
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);
    out<<(quint16)0<<msgType<<id;
    out.device()->seek(0);
//    qDebug()<<"porrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrt"<<(quint16)port.toUInt()+1;
    udpSocket->writeDatagram(block.data(),block.size(),QHostAddress(ip),(quint16)port.toUInt()+1);
    connect(this->udpSocket,SIGNAL(readyRead()),this,SLOT(recvMsg()));
}

void MainWindow::recvMsg()
{
    QByteArray block;
    QString msgType;
    QStringList idList;
    QStringList nameList;
    quint16 size;
    QHostAddress peerIp;
    quint16 peerPort;
    block.resize(udpSocket->pendingDatagramSize());
    this->udpSocket->readDatagram(block.data(),block.size(),&peerIp,&peerPort);
    QDataStream in(&block,QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_6);
    in>>size>>msgType;
    qDebug()<<"Dadadadadada";

    if("MSG_ALL_USER_ONLINE"==msgType)
    {
        qDebug()<<"get all user_online";
        in>>idList>>nameList;
        for(int i=0;i<idList.count();i++)
        {
            QString itemString;
            if(idList.at(i)!=id)
            {
              itemString = nameList.at(i)+"("+idList.at(i)+")";
              ui->userListWidget->addItem(itemString);
            }
        }
        //ui->countLabel->setText(QString::number(ui->UserListWidget->count())+" user online");
    }
    if("MSG_CLIENT_CHAT"==msgType)
    {
        QString peerName;
        QString peerId;
        QString msg;
        in>>peerName>>peerId>>msg;

        QString valueHash;
        valueHash.append(peerName+"("+peerId+")");
        chatForm *c;
        if(chatFormHash.contains(valueHash))
        {
            c=chatFormHash.value(valueHash);
        }
        else
        {
            c=new chatForm(this->id,this->ip,this->port,this->udpSocket);
            c->setWindowTitle("chatting with"+peerName+"("+peerId+").");
            chatFormHash.insert(valueHash,c);
        }
        c->show();
        c->displayText(peerName,peerId,msg);
    }
    if("MSG_SERVER_INFO"==msgType)
    {
        qDebug()<<"aaaaaaaaaaaaaaaa";
        QString msg;
        in>>msg;
        //ui->showListWidget->addItem("server:"+msg);
    }
    if("MSG_NEW_USER_LOGIN"==msgType)
    {
        QString peerName;
        QString peerId;
        QString user;
        in>>peerId>>peerName;
        if(this->id!=peerId)
        {
            user.append(peerName+"("+peerId+")");
            for(int i=0;i<ui->userListWidget->count();i++)
            {
                if(ui->userListWidget->item(i)->text()==user)
                {
                    delete ui->userListWidget->takeItem(i);
                }
            }
            ui->userListWidget->addItem(user);
            //ui->showListWidget->addItem(user+"login.");
            //ui->countLabel->setText(QString::number(ui->UserListWidget->count())+"user online");
        }
    }
    if("MSG_CLIENT_LOGOUT"==msgType)
    {
        QString peerName;
        QString peerId;
        QString userStr;
        in>>peerId>>peerName;
        userStr.append(peerName+"("+peerId+")");
        for(int i=0;i<ui->userListWidget->count();i++)
        {
            if(ui->userListWidget->item(i)->text()==userStr)
            {
                delete ui->userListWidget->takeItem(i);
            }
        }
        chatForm *c=chatFormHash.value(userStr);
        if(c!=0)
        {
            c->close();
            chatFormHash.remove(userStr);
        }
        //ui->showListWidget->addItem(userStr+"logout.");
        //ui->countLabel->setText(QString::number(ui->UserListWidget->count()));
    }
}


void MainWindow::userListWidget_itemDoubleClicked(QListWidgetItem* item)
{
    qDebug() << "userListWidget double clicked";
    QString nameStr=ui->userListWidget->currentItem()->text();
    nameStr.replace("\n","");
    QString tempstr(nameStr);
    chatForm *c=chatFormHash.value(nameStr);
    if(c==0)
    {
        c=new chatForm(this->id,this->ip,this->port,this->udpSocket);
        c->setWindowTitle("chatting with"+nameStr+".");
        chatFormHash.insert(nameStr,c);
        qDebug() << "double clicked c==0" ;
    }

    qDebug() << "double clicked c.show()";
    c->show();
}

void MainWindow::on_quitButton_clicked()
{
    QString msgType="MSG_USER_LOGOUT";
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);
    out<<(quint16)0<<msgType<<id;
    out.device()->seek(0);
    out<<(quint16)(block.size()-sizeof(quint16));
    if(!udpSocket->writeDatagram(block.data(),block.size(),QHostAddress(ip),(quint16)port.toUInt()+1))
    {
        QMessageBox::warning(NULL,tr("udpSocket"),tr("writeDatagram"));
    }
    this->close();
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    MainWindow::on_quitButton_clicked();
}


void MainWindow::on_userListWidget_itemDoubleClicked(QListWidgetItem* item)
{
    qDebug() << "userListWidget double clicked";
    QString nameStr=ui->userListWidget->currentItem()->text();
    nameStr.replace("\n","");
    QString tempstr(nameStr);
    chatForm *c=chatFormHash.value(nameStr);
    if(c==0)
    {
        c=new chatForm(this->id,this->ip,this->port,this->udpSocket);
        c->setWindowTitle("chatting with"+nameStr+".");
        chatFormHash.insert(nameStr,c);
        qDebug() << "double clicked c==0" ;
    }

    qDebug() << "double clicked c.show()";
    c->show();
}
