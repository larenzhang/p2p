#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QTcpSocket>
#include <QHostAddress>

namespace Ui {
    class registerDialog;
}

class registerDialog : public QDialog {
    Q_OBJECT
public:
    registerDialog(QString ip,QString port,QWidget *parent = 0);
    ~registerDialog();

protected:
    void changeEvent(QEvent *e);
protected slots:
    void confirmRegisterInfo();
    void receiveSockets();
    void disconnectedStatus();
    void displaySocketError(QAbstractSocket::SocketError socketError);

private:
    Ui::registerDialog *ui;
    QTcpSocket *tcpSocket;
    QString    ip;
    QString    port;


};

#endif // REGISTERDIALOG_H
