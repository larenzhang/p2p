#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sqlitedb.h"
#include "tcpsockserver.h"
#include "tcpconthread.h"
#include "mysqlquerymodel.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QString ip;
    QString port;

    TcpSockServer server;
    QUdpSocket *udpSocket;
    SqliteDB *Sqdb;
    MySqlQueryModel *model;
    QTableView *view;



    QHostAddress senderIp;
    quint16 senderPort;


    void processDatagram(QByteArray block);
    void tableViewRefresh();

private slots:
    void on_startListPushButton_clicked();
    void on_read_Datagrams();
    void on_about_Connection();
};

#endif // MAINWINDOW_H
