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
    static bool execSql(QWidget *parent,QSqlQuery &query,QString sql,QString title, QString errorMsg);
private:
    QSqlDatabase db;
};

#endif // DBSETTING_H
