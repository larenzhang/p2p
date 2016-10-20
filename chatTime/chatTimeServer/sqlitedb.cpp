#include "sqlitedb.h"

SqliteDB::SqliteDB(QObject *parent) :
    QObject(parent)
{
        QSqlDatabase dbb = QSqlDatabase::addDatabase("QSQLITE");
        dbb.setDatabaseName("chat.db");
        if (!dbb.open()) {
                 qDebug()<<"db0 not opem";
                 return  ;
             }

         QSqlQuery query(dbb);
         query.exec(QLatin1String("create table user (id int primary key,password int ,name char ,logstat char,ip char,port char)"));
   //      query.exec(QObject::tr("INSERT INTO user VALUES( 503 , 503 ,'a','0','255.255.255.255',1111 )"));
   //      query.exec(QObject::tr("INSERT INTO user VALUES( 504 , 504 ,'b','0','255.255.255.255',1111)"));

}

SqliteDB::~SqliteDB()
{
    this->connectDB();
    QSqlQuery query;

    query.prepare("SELECT * from user ");
    if(!(query.exec()))
    {
         QMessageBox::critical(NULL,"exec","exec failed");
    }
    while(query.next())
    {
         query.value(3) = "0";
    }

    this->closeDB();
}

void SqliteDB::showAll()
{
    this->connectDB();
    QSqlQuery query;

    query.prepare("SELECT * from user ");
    if(!(query.exec()))
    {
         QMessageBox::critical(NULL,"exec","exec failed");
    }
    while(query.next())
    {
         qDebug()<<query.value(0).toInt()<<query.value(1).toInt()<<query.value(2).toString()<<query.value(3).toString()<<query.value(4).toString()<<query.value(5).toString();
    }

    this->closeDB();
}

void SqliteDB::connectDB()
{

    db = QSqlDatabase::database();
    if (!db.open()) {
             qDebug()<<"db3 not opem";
             return  ;
         }

/*    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("chat.db");
    if (!db.open()) {
             qDebug()<<"db0 not opem";
             return  ;
         }

     QSqlQuery query(db);
     query.exec(QLatin1String("create table user (id int primary key,password int ,name char ,logstat char,ip char)"));
     query.exec(QObject::tr("INSERT INTO user VALUES( 503 , 503 ,'a','0','255.255.255.255' )"));
     query.exec(QObject::tr("INSERT INTO user VALUES( 504 , 504 ,'b','0','255.255.255.255')"));

    if (!db.open()) {
             qDebug()<<"db not opem";
             return  ;
         }
   */
}

void SqliteDB::closeDB()
{
    db.close();
}

void SqliteDB::getUserInfo(QString id)
{
    this->connectDB();
    QSqlQuery query;
    strListUser.clear();

    query.prepare("SELECT id,password,name,logstat,ip from user where id=?");
    query.addBindValue(id);
    if(!(query.exec()))
    {
         QMessageBox::critical(NULL,"exec","exec failed");
    }

    while(query.next())
    {
        if(query.value(0).toString()==id)
        {
            strListUser.append(query.value(0).toString());
            strListUser.append(query.value(1).toString());
            strListUser.append(query.value(2).toString());
            strListUser.append(query.value(3).toString());
            strListUser.append(query.value(4).toString());
        }
    }
    this->closeDB();
}

void SqliteDB::updateUserLogStat(QString id, QString stat)
{
    this->connectDB();
    QSqlQuery query;
    strListUser.clear();

    query.prepare("update user set logstat=? where id=?");
    query.addBindValue(stat);
    query.addBindValue(id);
    if(!(query.exec()))
    {
         QMessageBox::critical(NULL,"exec","exec failed");
    }
    this->closeDB();
}

void SqliteDB::updateUserIp(QString id, QString ip)
{
    this->connectDB();
    QSqlQuery query;
    strListUser.clear();

    query.prepare("update user set ip=? where id=?");
    query.addBindValue(ip);
    query.addBindValue(id);
    if(!(query.exec()))
    {
         QMessageBox::critical(NULL,"exec","exec failed");
    }
    this->closeDB();
}

void SqliteDB::getUserAllOnline()
{
    this->connectDB();
    QSqlQuery query;
    strListId.clear();
    strListName.clear();

    query.prepare("select id,name from user where logstat =1");
    if(!(query.exec()))
    {
         QMessageBox::critical(NULL,"exec","exec failed");
    }
    while(query.next())
    {
        strListId.append(query.value(0).toString());
        strListName.append(query.value(1).toString());
    }
    this->closeDB();
}

int SqliteDB::insertNewUser(QString id, QString password, QString name, QString ip, QString port)
{

  // qDebug()<<"rr"<<id<<password<<name<<ip<<port;
    this->connectDB();
    QSqlQuery query;
    query.prepare("select id from user ");
    if(!(query.exec()))
    {
         QMessageBox::critical(NULL,"exec","exec failed");
         return -1;
    }
    while(query.next())
    {
        if(query.value(0).toString()==id)
        {
            return 0;
        }
    }
    query.prepare(QObject::tr("INSERT INTO user VALUES(?,?,?,'0',?,?)"));
    query.addBindValue(id);
    query.addBindValue(password);
    query.addBindValue(name);
    query.addBindValue(ip);
    query.addBindValue(port);
    query.exec();

    this->closeDB();
    return 1;

}
