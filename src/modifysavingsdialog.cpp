#include "modifysavingsdialog.h"
#include "ui_modifysavingsdialog.h"
#include <QMessageBox>
#include <QRegularExpression>

ModifySavingsDialog::ModifySavingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifySavingsDialog)
{
    ui->setupUi(this);
}

ModifySavingsDialog::~ModifySavingsDialog()
{
    delete ui;
}

void ModifySavingsDialog::setDb(QSqlDatabase db){
    this->db = db;
}

void ModifySavingsDialog::receiveModify(int saving_id,QString savingsSystem,QString balance){
    this->setWindowModality(Qt::ApplicationModal);
    this->saving_id = saving_id;
    this->savingsSystem = savingsSystem;
    this->balance = balance;
    this->ui->savingSystemLE->setText(this->savingsSystem);
    this->ui->balanceLE->setText(this->balance);
    this->show();
}

void ModifySavingsDialog::on_conformBtn_clicked(){
    QString sql;
    QSqlQuery query;
    QRegularExpression rx("-?[0-9]+(.[0-9]{1,2})?$");
    if(! rx.match(this->ui->balanceLE->text()).hasMatch()){
        QMessageBox::warning(this,"注意！","金额格式不正确!");
        return;
    }
    sql = QString("update user_savings set balance = %1 where id = %2;").arg(this->ui->balanceLE->text()).arg(this->saving_id);
//    qDebug() << sql;
    if(!DBSetting::execSql(this,query,sql,"错误","错误代码 : ")){
        return;
    }
    QMessageBox::information(this,"提示","修改成功!");
    this->hide();
    emit flushMainWindow();
}
void ModifySavingsDialog::on_returnBtn_clicked(){
    this->hide();
}
