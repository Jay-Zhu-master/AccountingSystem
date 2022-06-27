
#include "registdialog.h"
#include "ui_registdialog.h"
#include "dbsetting.h"
#include <QMessageBox>

RegistDialog::RegistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistDialog)
{
    ui->setupUi(this);
}

RegistDialog::~RegistDialog()
{
    delete ui;
}

void RegistDialog::setDB(QSqlDatabase db){
    this->db = db;
}

void RegistDialog::receiveRegist(){
    this->show();
}
void RegistDialog::on_conformBtn_clicked(){
    QString sql1;
    QSqlQuery query;
    if(this->ui->usernameLE->text().length() < 6 || this->ui->usernameLE->text().length() > 16){
        QMessageBox::information(this,"提示！","用户名长度须在6~16位之间！");
        return;
    }
    if(this->ui->passwordLE->text().length() < 6 || this->ui->passwordLE->text().length() > 16){
        QMessageBox::information(this,"提示！","密码长度须在6~16位之间！");
        return;
    }
    sql1 = QString("select count(1) from user_info where username = '%1'").arg(this->ui->usernameLE->text());
    qDebug() << sql1;
    query.exec(sql1);
    query.next();
    qDebug() << query.value(0).toInt();
    if(query.value(0).toInt() != 0){
        QMessageBox::information(this,"提示！","用户名已存在！");
        return;
    }
    sql1 = QString("insert into user_info(username,password,wight) values ('%1','%2',1)")
            .arg(this->ui->usernameLE->text())
            .arg(this->ui->passwordLE->text());
    qDebug() << sql1;
    query.exec(sql1);
    QMessageBox::information(this,"提示","注册成功！");
    this->hide();
    emit returnLogin();
}
void RegistDialog::on_returnBtn_clicked(){
    this->hide();
    emit returnLogin();
}
