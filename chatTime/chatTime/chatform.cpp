#include "chatform.h"
#include "ui_chatform.h"

chatForm::chatForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chatForm)
{
    ui->setupUi(this);
}

chatForm::chatForm(QString id,QString peerIp,QString peerPort,QUdpSocket *udpSocket):ui(new Ui::chatForm)
{
    this->id=id;
    this->serverIp=peerIp;
    this->serverPort=peerPort;
    this->udpSocket=udpSocket;
    ui->setupUi(this);
}

chatForm::~chatForm()
{
    delete ui;
}

void chatForm::closeEvent(QCloseEvent *e)
{
    ui->displayListWidget->clear();
    ui->inputTextEdit->clear();
    //this->close();
}

void chatForm::displayText(QString name, QString id, QString text)
{
    QListWidgetItem *displayItem=new QListWidgetItem(name+"("+id+"):\n"+text+"\n");
    ui->displayListWidget->addItem(displayItem);
}

void chatForm::on_sendButton_clicked()
{
    QString sendText=ui->inputTextEdit->toPlainText();
    if(!sendText.isEmpty())
    {
        QString windowTitle=this->windowTitle().replace(").","");
        QString toId=QString(windowTitle.split("(").at(1));
        QString msgType="MSG_CLIENT_CHAT";
        QByteArray block;
        QDataStream out(&block,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_6);
        out<<(quint16)0<<msgType<<id<<toId<<sendText;
        out.device()->seek(0);
        out<<(quint16)(block.size()-sizeof(quint16));
        udpSocket->writeDatagram(block.data(),block.size(),QHostAddress(serverIp),(quint16)serverPort.toUInt()+1);
        ui->displayListWidget->addItem("I say :\n"+sendText+"\n");
    }
    ui->inputTextEdit->clear();
}
