#ifndef DBSETTING_H
#define DBSETTING_H

#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>


class DBSetting
{
public:
    DBSetting();
    QSqlDatabase getDb();
private:
    QSqlDatabase db;
};

#endif // DBSETTING_H
