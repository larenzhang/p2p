#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Sqdb=new SqliteDB;
    ip.clear();
    port.clear();

    udpSocket=new QUdpSocket(this);

    connect(&server,SIGNAL(newConnection()),this,SLOT(on_about_Connection()));
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(on_read_Datagrams()));

    tableViewRefresh();

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

void MainWindow::on_about_Connection()
{
   // server.incomingConnection();
  //  QMessageBox::information(NULL,tr("提示"),tr("新连接创建成功。"));
    tableViewRefresh();
}

void MainWindow::on_startListPushButton_clicked()
{
    ip.clear();
    port.clear();
    ip=ui->ipLineEdit->text().trimmed();
    port=ui->portLineEdit->text().trimmed();

    if(ui->startListPushButton->text()=="开始监听")
    {
        server.close();

        QRegExp rxIp("\\d+\\.\\d+\\.\\d+\\.\\d+");
        QRegExp rxPort(("[1-9]\\d{3,4}"));
        rxIp.setPatternSyntax(QRegExp::RegExp);
        rxPort.setPatternSyntax(QRegExp::RegExp);

        if(!rxPort.exactMatch(port)||!rxIp.exactMatch(ip))
        {
            QMessageBox::critical(NULL,tr("提示"),tr("请输入正确的IP和端口"));
        }
        else
        {
            if(!server.listen(QHostAddress(ip),(quint16)port.toUInt()))
            {
                QMessageBox::critical(NULL,tr("提示"),tr("TCP 监听失败：%1.").arg(server.errorString()));
            }
            else
            {
                udpSocket=new QUdpSocket(this);
                if(!udpSocket->bind(QHostAddress(ip),(quint16)port.toUInt()+1))
                {
                   QMessageBox::critical(NULL,tr("提示"),tr("TCP 监听失败：%1.").arg(server.errorString()));
                }
                connect(udpSocket,SIGNAL(readyRead()),this,SLOT(on_read_Datagrams()));
                ui->startListPushButton->setText("断开监听");
                ui->ipLineEdit->setEnabled(false);
                ui->portLineEdit->setEnabled(false);
            }
        }
    }
    else if("断开监听"==ui->startListPushButton->text())
    {
        server.close();
        udpSocket->close();
        ui->startListPushButton->setText("开始监听");
        ui->ipLineEdit->setEnabled(true);
        ui->portLineEdit->setEnabled(true);
    }
}

void MainWindow::on_read_Datagrams()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray block;
        block.resize(udpSocket->pendingDatagramSize());
        if(-1==udpSocket->readDatagram(block.data(),block.size(),&senderIp,&senderPort))
            continue;

        processDatagram(block);
    }
}

void MainWindow::processDatagram(QByteArray block)
{
    QDataStream in(&block,QIODevice::ReadOnly);
    quint16 dataGramSize;
    QString msgType;
    in>>dataGramSize>>msgType;
    if("MSG_CLIENT_NEW_CONN"==msgType)
    {
        QString id;
        in>>id;
        if(!id.isEmpty())
        {   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!this FUCKING senderPort Changed!!!
            qDebug()<<"senderPort:"<<senderPort;
            tableViewRefresh();
        }
        Sqdb->getUserAllOnline();
        QStringList idList=Sqdb->strListId;
        QStringList nameList=Sqdb->strListName;

        QString msgType="MSG_ALL_USER_ONLINE";
        QByteArray block;
        QDataStream out(&block,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_6);
        out<<(quint16)0<<msgType<<idList<<nameList;
        out.device()->seek(0);
        out<<(quint16)(block.size()-sizeof(quint16));
        /*
        if(!udpSocket->writeDatagram(block.data(),block.size(),this->senderIp,this->senderPort))
        {
            QMessageBox::critical(NULL,tr("提示"),tr("!udpSocket->writeDatagram."));
        }
        */
        if(!udpSocket->writeDatagram(block.data(),block.size(),QHostAddress::Broadcast,6666))
        {
            QMessageBox::critical(NULL,tr("提示"),tr("!udpSocket->writeDatagram."));
        }


        qDebug() <<"get all user online!";
        /*
        msgType="MSG_NEW_USER_LOGIN";
        block.clear();
        out.device()->seek(0);
        Sqdb->getUserInfo(id);

        out<<(quint16)0<<msgType<<id<<Sqdb->strListUser.at(2);
        out.device()->seek(0);
        out<<(quint16)(block.size()-sizeof(quint16));
        if(!udpSocket->writeDatagram(block.data(),block.size(),QHostAddress("255.255.255.255"),this->senderPort))
        {
             QMessageBox::critical(NULL,tr("提示"),tr("!udpSocket->writeDatagram."));
        }
        */
    }
    else if("MSG_CLIENT_REGISTER_SUCCESS"==msgType)
    {
        qDebug()<<"MSG_CLIENT_REGISTER_SUCCESS:"<<senderPort;
        tableViewRefresh();

    }
    else if("MSG_USER_LOGOUT"==msgType)
    {
        QString id;
        in>>id;
        if(id.isEmpty())
        {
            ;
        }
        else
        {
           Sqdb->updateUserLogStat(id,"0");
           this->tableViewRefresh();
           msgType="MSG_CLIENT_LOGOUT";
           block.clear();
           QDataStream out(&block,QIODevice::WriteOnly);
           out.device()->seek(0);
           Sqdb->getUserInfo(id);
           out<<(quint16)0<<msgType<<id<<Sqdb->strListUser.at(0);
           out.device()->seek(0);
           out<<(quint16)(block.size()-sizeof(quint16));
           if(!udpSocket->writeDatagram(block.data(),block.size(),QHostAddress::Broadcast,6666))
           {
               QMessageBox::critical(NULL,tr("提示"),tr("!udpSocket->writeDatagram."));
           }
        }
     }
    else if("MSG_CLIENT_CHAT"==msgType)
     {
         QString toid,fromId,fromName,toIp,buffer;
         in>>fromId>>toid>>buffer;
         Sqdb->getUserInfo(toid);
         toIp=Sqdb->strListUser.at(4);
         Sqdb->getUserInfo(fromId);
         fromName=Sqdb->strListUser.at(2);
         QByteArray blockTosend;
         QDataStream tosend(&blockTosend,QIODevice::WriteOnly);
         QString mytype="MSG_CLIENT_CHAT";
         tosend<<(quint16)0<<mytype<<fromName<<fromId<<buffer;
         tosend.device()->seek(0);
         tosend<<(quint16)(blockTosend.size()-sizeof(quint16));
         if(!udpSocket->writeDatagram(blockTosend.data(),blockTosend.size(),QHostAddress(toIp),6666))
             QMessageBox::warning(NULL,"message sending","error");
       }
}

void MainWindow::tableViewRefresh()
{
    Sqdb->connectDB();
    model = new MySqlQueryModel;
    model->setQuery(QObject::tr("select id,name,logstat,ip,port from user"));
    model->setHeaderData(0, Qt::Horizontal, tr("Id号"));
    model->setHeaderData(1, Qt::Horizontal, tr("昵称"));
    model->setHeaderData(2, Qt::Horizontal, tr("状态"));
    model->setHeaderData(3, Qt::Horizontal, tr("IP"));
    model->setHeaderData(4, Qt::Horizontal, tr("PORT"));

    view= new QTableView(this);
    view->setModel(model);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
    view->setGeometry(29,19,521,241);
    view->setColumnWidth(0, 104);
    view->setColumnWidth(1, 104);//设置列宽度
    view->setColumnWidth(2, 104);
    view->setColumnWidth(3, 104);
    view->setColumnWidth(4, 104);
    view->show();
    Sqdb->closeDB();
}
