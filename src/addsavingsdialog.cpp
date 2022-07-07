#include "addsavingsdialog.h"
#include "ui_addsavingsdialog.h"
#include <QRegExp>
#include <QMessageBox>

AddSavingsDialog::AddSavingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSavingsDialog)
{
    ui->setupUi(this);
}

AddSavingsDialog::~AddSavingsDialog()
{
    delete ui;
}

void AddSavingsDialog::setDB(QSqlDatabase db){
    this->db = db;
}

//void on_conformBtn_clicked();
//void on_returBtn_clicked();
//void receiveAddSavings();

void AddSavingsDialog::on_conformBtn_clicked(){
    QSqlQuery query;
    QString sql;
    QRegExp rx("-?[0-9]+(.[0-9]{1,2})?$");
    if(this->ui->savingSystemLE->text() == ""){
        QMessageBox::warning(this,"注意！","请输入存款位置！");
        return;
    }
    if(! rx.exactMatch(this->ui->balanceLE->text())){
        QMessageBox::warning(this,"注意！","金额格式不正确!");
        return;
    }
    sql = QString("insert into user_savings(user_id,saving_system,balance) values (%1,'%2',%3);")
            .arg(this->user_id).arg(this->ui->savingSystemLE->text()).arg(this->ui->balanceLE->text().toDouble());
//    qDebug() << sql;

    if(!DBSetting::execSql(this,query,sql,"警告","增加失败，错误代码 : ")){
        return;
    }
    emit flushMainWindow();
    this->hide();
}
void AddSavingsDialog::on_returnBtn_clicked(){
    this->hide();
}

void AddSavingsDialog::receiveAdd(){
    this->setWindowModality(Qt::ApplicationModal);
    this->ui->savingSystemLE->setText("");
    this->ui->balanceLE->setText("");
    this->show();
}

void AddSavingsDialog::setUserId(int user_id){
//    qDebug() << user_id;
    this->user_id = user_id;
}
