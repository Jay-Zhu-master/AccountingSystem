#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QCryptographicHash>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent),
                                            ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::setDB(QSqlDatabase db)
{
    this->db = db;
}

void LoginDialog::receiveReturn()
{
    this->show();
}

void LoginDialog::on_loginBtn_clicked()
{
    QString sql;
    QSqlQuery query;
    if (this->ui->usernameLE->text() == "")
    {
        QMessageBox::information(this, "提示", "请输入用户名！");
        return;
    }
    if (this->ui->passwordLE->text() == "")
    {
        QMessageBox::information(this, "提示", "请输入密码！");
        return;
    }
    sql = QString("select count(1) from user_info where username = '%1';").arg(this->ui->usernameLE->text());
//    qDebug() << sql;
    if(!DBSetting::execSql(this,query,sql,"错误","错误代码 : ")){
        return;
    }
    query.next();
    if (query.value(0).toInt() == 0)
    {
        QMessageBox::information(this, "提示", "用户不存在，创建一个吧！");
        return;
    }
    sql = QString("select * from user_info where username = '%1';").arg(this->ui->usernameLE->text());
//    qDebug() << sql;
    if(!DBSetting::execSql(this,query,sql,"错误","错误代码 : ")){
        return;
    }
    query.next();
//    qDebug() << QString(QCryptographicHash::hash(this->ui->passwordLE->text().toLatin1(),QCryptographicHash::Md5).toHex());
    if (QString(QCryptographicHash::hash(this->ui->passwordLE->text().toLatin1(),QCryptographicHash::Md5).toHex())
            != query.value("password").toString())
    {
        QMessageBox::information(this, "提示", "密码错误！");
        return;
    }
    this->hide();
//    qDebug() << query.value("user_id");
    this->user_id = query.value("user_id").toInt();
    emit loginSuccess(this->user_id);
}
void LoginDialog::on_registBtn_clicked()
{
    this->hide();
    emit registSignal();
}
void LoginDialog::on_quitBtn_clicked()
{
    emit quit();
}
int LoginDialog::getUserId()
{
    return this->user_id;
}
