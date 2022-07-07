#include "dbsetting.h"
#include <QMessageBox>

DBSetting::DBSetting()
{
    qDebug() << QSqlDatabase::drivers();
    this->db = QSqlDatabase::addDatabase("QMYSQL");
    this->db.setHostName("101.43.215.142");
    this->db.setPort(3306);
    this->db.setDatabaseName("accounting_system");
    this->db.setUserName("jayzhu");
    this->db.setPassword("Zlh123..");
    if(this->db.open()){
        qDebug() << "ok";
    }else{
        qDebug() << "fail";
    }
}

QSqlDatabase DBSetting::getDb(){
    return this->db;
}

bool DBSetting::execSql(QWidget *parent,QSqlQuery &query, QString sql, QString title, QString errorMsg){
    if(!query.exec(sql)){
        QMessageBox::warning(parent,title,errorMsg + query.lastError().text());
        return false;
    }
    return true;
}
