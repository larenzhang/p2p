#ifndef SQLITEDB_H
#define SQLITEDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QString>
#include <QStringList>
#include <QDebug>

class SqliteDB : public QObject
{
    Q_OBJECT
public:
    explicit SqliteDB(QObject *parent = 0);
    ~SqliteDB();

    QStringList strListUser;
    QStringList strListId;
    QStringList strListName;

    void connectDB();
    void closeDB();
    void getUserInfo(QString id);
    void updateUserLogStat(QString id,QString stat);
    int  insertNewUser(QString id,QString password,QString name,QString ip,QString port);
    void getUserAllOnline();
    void updateUserIp(QString id,QString ip);
    void updateUserPort(QString id, quint16 port);
    void showAll();

private:
    QSqlDatabase db;

signals:

public slots:

};

#endif // SQLITEDB_H
