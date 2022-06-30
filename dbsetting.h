#ifndef DBSETTING_H
#define DBSETTING_H

#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>


class DBSetting
{
public:
    DBSetting();
    QSqlDatabase getDb();
private:
    QSqlDatabase db;
};

#endif // DBSETTING_H
