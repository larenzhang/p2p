#ifndef MYSQLQUERYMODEL_H
#define MYSQLQUERYMODEL_H

#include <QSqlQueryModel>
#include <QSqlQuery>

class MySqlQueryModel : public QSqlQueryModel
{
public:
    MySqlQueryModel();
    QVariant data(const QModelIndex &item,int role=Qt::DisplayPropertyRole) const;
};

#endif // MYSQLQUERYMODEL_H
