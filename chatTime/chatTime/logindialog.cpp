#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox.h>
#include <QDebug.h>
loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);

    // for test, to be deleted
    this->setWindowTitle("Login");
    ui->idLineEdit->setText("12345");
    ui->pwLineEdit->setText("12345");
    ui->ipLineEdit->setText("127.0.0.1");
    ui->portLineEdit->setText("12345");

    settingFlag = true;
    ip.clear();
    port.clear();
    tcpSocket =new QTcpSocket(this);

    connect(ui->setPushButton,SIGNAL(clicked()),this,SLOT(setNetInformation()));

//    connect(ui->loginPushButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->loginPushButton,SIGNAL(clicked()),this,SLOT(loginSystem()));

 //   connect(ui->registerPushButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->registerPushButton,SIGNAL(clicked()),this,SLOT(showRegisterDlg()));

    connect(ui->confirmPushButton,SIGNAL(clicked()),this,SLOT(confirmNetInformation()));

    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(receiveSockets()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disconnectedStatus()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displaySocketError(QAbstractSocket::SocketError)));
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::changeEvent(QEvent *e)
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

void loginDialog::loginSystem()
{
//    for test,set user accout
    ip = "127.0.0.1";
    port = "12345";

    if(ip.isEmpty() || port.isEmpty())
    {
        QMessageBox::warning(NULL,tr("��ʾ"),tr("��������IP�Ͷ˿�"));
    }
    else
    {
        id=ui->idLineEdit->text().trimmed();
        password=ui->pwLineEdit->text().trimmed();

        QRegExp rx("^[1-9]{1,2}[0-9]{4,7}$");
        rx.setPatternSyntax(QRegExp::RegExp);
        if(!rx.exactMatch(id))
        {
            QMessageBox::warning(NULL,tr("��ʾ"),tr("������5��9λ�����ʺ�"));
        }
        else
        {
             tcpSocket->abort();
             tcpSocket->connectToHost(QHostAddress(ip),(quint16)port.toUInt());
             QString msgType="MSG_USER_LOGIN";
            // QString msgType="MSG_CLIENT_REGISTER_SUCCESS";

             QByteArray block;
             QDataStream out(&block,QIODevice::WriteOnly);
             out.setVersion(QDataStream::Qt_4_6);
             out<<(quint16)0<<msgType<<id<<password;
             out.device()->seek(0);
             out<<(quint16)(block.size()-sizeof(quint16));
             tcpSocket->write(block);
//             qDebug()<<"qqqqqqqqqqqqqqqqq";
        }
    }

}

void loginDialog::showRegisterDlg()
{
    registerDlg = new registerDialog(ip,port);
    this->registerDlg->show();
}


void loginDialog::setNetInformation()
{
    if(settingFlag)
    {
        this->resize(400,408);
     // ui->setPushButton->setText("����>");
    }
    else
    {
        this->resize(400,280);
     // ui->setPushButton->setText("����^");
    }

    settingFlag = !settingFlag;
}

void loginDialog::confirmNetInformation()
{
    ip=ui->ipLineEdit->text().trimmed();
    port=ui->portLineEdit->text().trimmed();

    QRegExp rxIp("\\d+\\.\\d+\\.\\d+\\.\\d+");
    QRegExp rxPort(("[1-9]\\d{2,4}"));

    rxIp.setPatternSyntax(QRegExp::RegExp);
    rxPort.setPatternSyntax(QRegExp::RegExp);

    if(!rxPort.exactMatch(port)||!rxIp.exactMatch(ip))
    {
        ip.clear();
        port.clear();
        QMessageBox::critical(NULL,tr("��ʾ"),tr("��������ȷ��IP�Ͷ˿�"));
    }
    else
    {
        this->resize(401,280);
     // ui->setButton->setText("����>");
        settingFlag = !settingFlag;
    }

    qDebug()<<ip<<" "<<port;
}

void loginDialog::receiveSockets()
{
    QByteArray block=tcpSocket->readAll();
    QDataStream in(&block,QIODevice::ReadOnly);
    quint16 dataGramSize;
    QString msgType;
    in>>dataGramSize>>msgType;

    if("MSG_ID_NOTEXIST"==msgType)
    {
        QMessageBox::warning(NULL,tr("��ʾ"),tr("�ú��벻���ڣ�����ע��"));
    }
    else if("MSG_LOGIN_SUCCESS"==msgType)
    {
        mainWindow = new MainWindow(id,ip,port);
        mainWindow->setWindowTitle(tr("ChatTime"));
        mainWindow->show();
        this->close();
    }
    else if("MSG_PWD_ERROR"==msgType)
    {
        QMessageBox::information(NULL,tr("��ʾ"),tr("�������"));
    }
    else if("MSG_LOGIN_ALREADY"==msgType)
    {
        QMessageBox::information(NULL,tr("��ʾ"),tr("��Ҫ�ظ���¼"));
    }
}

void loginDialog::disconnectedStatus()
{
    QMessageBox::warning(NULL,tr("��ʾ"),tr("��ʧȥ�����������"));
}

void loginDialog::displaySocketError(QAbstractSocket::SocketError socketError)
{
    if(socketError!=QAbstractSocket::RemoteHostClosedError)
    {
        QMessageBox::warning(NULL,tr("��ʾ"),tr("�����д���%1").arg(tcpSocket->errorString()));
    }
}
