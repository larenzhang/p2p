#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QMessageBox.h>
#include <QUdpSocket.h>

registerDialog::registerDialog(QString ip,QString port,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerDialog)
{
    ui->setupUi(this);

    this->ip = ip;
    this->port = port;
    tcpSocket =new QTcpSocket(this);

    connect(ui->confirmPushButton,SIGNAL(clicked()),this,SLOT(confirmRegisterInfo()));
    connect(ui->cancelPushButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(receiveSockets()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disconnectedStatus()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displaySocketError(QAbstractSocket::SocketError)));
}

registerDialog::~registerDialog()
{
    delete ui;
}

void registerDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void registerDialog::confirmRegisterInfo()
{
    QString id=ui->idLineEdit->text().trimmed();
    QString password=ui->pwdLineEdit->text().trimmed();
    QString againPassword=ui->rePwdLineEdit->text().trimmed();
    QString name=ui->nameLineEdit->text().trimmed();

    QRegExp rx("^[1-9]{1,2}[0-9]{4,7}$");
    rx.setPatternSyntax(QRegExp::RegExp);
    if(!rx.exactMatch(id))
    {
        QMessageBox::warning(NULL,tr("��ʾ"),tr("������5��9λ���˺š�"));
    }
    else if((password!=againPassword)||(password.size()>9)||(password.size()==0))
    {
        QMessageBox::warning(NULL,tr("��ʾ"),tr("������1��9λ�����룬����Ҫһ��"));
    }
    else if(name.size()==0)
    {
        QMessageBox::warning(NULL,tr("��ʾ"),tr("�ǳƲ���Ϊ��"));
    }
    else
    {
        qDebug()<<"dd"<<id<<" "<<name<<password<< " "<<ip<<" "<<port;
        if(1)
        {
            tcpSocket->abort();
            tcpSocket->connectToHost(QHostAddress(ip),(quint16)port.toUInt());
            qDebug()<<"MSG_CLIENT_USER_REGISTER"<<ip<<port;
            QString msgType="MSG_CLIENT_USER_REGISTER";
            QByteArray block;
            QDataStream out(&block,QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_4_6);
            out<<(quint16)0<<msgType<<id<<password<<name;
            out.device()->seek(0);
            out<<(quint16)(block.size()-sizeof(quint16));
            tcpSocket->write(block);
        }
   }
}


void registerDialog::receiveSockets()
{
    QByteArray block=tcpSocket->readAll();
    QDataStream in(&block,QIODevice::ReadOnly);
    quint16 dataGramSize;
    QString msgType;
    in>>dataGramSize>>msgType;

    if("MSG_ID_ALREADY_EXIST"==msgType)
    {
        QMessageBox::warning(NULL,tr("��ʾ"),tr("�ú�����ע��"));
    }
    else if("MSG_CLIENT_REGISTER_SUCCESS"==msgType)
    {
        qDebug()<<"mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm"<<(quint16)port.toUInt()+1;
        QString msgType="MSG_CLIENT_REGISTER_SUCCESS";
        QByteArray block;
        QDataStream out(&block,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_6);
        out<<(quint16)0<<msgType;
        out.device()->seek(0);
        out<<(quint16)(block.size()-sizeof(quint16));
        QUdpSocket *udpSocket=new QUdpSocket(this);
       // udpSocket->writeDatagram(block.data(),block.size(),QHostAddress(ip),(quint16)port.toUInt()+1);
        if(!udpSocket->writeDatagram(block.data(),block.size(),QHostAddress(ip),(quint16)port.toUInt()+1))
        {
            QMessageBox::warning(NULL,tr("udpSocket"),tr("writeDatagram"));
        }
        QMessageBox::warning(NULL,tr("��ʾ"),tr("ע��ɹ�"));
        this->close();
    }
}


void registerDialog::disconnectedStatus()
{
    QMessageBox::warning(NULL,tr("��ʾ"),tr("��ʧȥ�����������"));
}

void registerDialog::displaySocketError(QAbstractSocket::SocketError socketError)
{
    if(socketError!=QAbstractSocket::RemoteHostClosedError)
    {
        QMessageBox::warning(NULL,tr("��ʾ"),tr("�����д���%1").arg(tcpSocket->errorString()));
    }
}
