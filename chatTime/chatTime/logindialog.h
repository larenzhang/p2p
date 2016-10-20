#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QRegExp>
#include <QTcpSocket>
#include <QHostAddress>

#include "mainwindow.h"
#include "registerdialog.h"

namespace Ui {
    class loginDialog;
}

class loginDialog : public QDialog {
    Q_OBJECT
public:
    loginDialog(QWidget *parent = 0);
    ~loginDialog();

protected:
    void changeEvent(QEvent *e);

protected slots:
    void loginSystem();
    void showRegisterDlg();
    void setNetInformation();
    void confirmNetInformation();
    void receiveSockets();
    void disconnectedStatus();
    void displaySocketError(QAbstractSocket::SocketError socketError);

private:
    Ui::loginDialog *ui;
    MainWindow      *mainWindow;
    registerDialog  *registerDlg;
    QTcpSocket *tcpSocket;
    bool            settingFlag;
    QString         ip;            //ip地址
    QString         port;          //端口号
    QString         id;            //用户id
    QString         password;      //用户密码
};

#endif // LOGINDIALOG_H
