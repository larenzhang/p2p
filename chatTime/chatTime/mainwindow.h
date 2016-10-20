#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QHostAddress>
#include <QListWidgetItem>
#include "chatform.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QString id,QString ip,QString port,QWidget *parent = 0);
    ~MainWindow();
    void init();
public slots:
    void userListWidget_itemDoubleClicked(QListWidgetItem* item);

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *e);

private:
    Ui::MainWindow *ui;
    QString ip;
    QString port;
    QString id;

    QUdpSocket *udpSocket;
    QHash<QString,chatForm *> chatFormHash;
private slots:
    void on_userListWidget_itemDoubleClicked(QListWidgetItem* item);
    void on_quitButton_clicked();
    void recvMsg();
};

#endif // MAINWINDOW_H
