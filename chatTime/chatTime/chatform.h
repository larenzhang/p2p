#ifndef CHATFORM_H
#define CHATFORM_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QUdpSocket>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QByteArray>
#include <QCloseEvent>

namespace Ui {
    class chatForm;
}

class chatForm : public QWidget
{
    Q_OBJECT

public:
    chatForm(QWidget *parent = 0);
    chatForm(QString id,QString peerIp,QString peerPort,QUdpSocket *udpSocket);
    ~chatForm();
    void displayText(QString name,QString id,QString text);

protected:
    void closeEvent(QCloseEvent *e);

private:
    Ui::chatForm *ui;
    QString serverIp;
    QString serverPort;
    QString id;
    QUdpSocket *udpSocket;

private slots:
    void on_sendButton_clicked();
};

#endif // CHATFORM_H
