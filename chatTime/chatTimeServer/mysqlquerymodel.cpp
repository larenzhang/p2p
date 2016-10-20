#include "mysqlquerymodel.h"

MySqlQueryModel::MySqlQueryModel()
{
}

QVariant MySqlQueryModel::data(const QModelIndex &index, int role)const
{
    QVariant value=QSqlQueryModel::data(index,role);
    if(value.isValid() &&  role==Qt::DisplayRole && index.column()==2)
    {
        value=(value.toInt()==1?tr("on_line"):tr("off_line"));
        return value;
    }
}
