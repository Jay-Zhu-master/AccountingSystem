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
    QRegExp rx("^[0-9]+(.[0-9]{1,2})?$");
    if(! rx.exactMatch(this->ui->balanceLE->text())){
        QMessageBox::warning(this,"注意！","金额格式不正确");
        return;
    }
    this->hide();
}
void AddSavingsDialog::on_returnBtn_clicked(){
    this->hide();
}

void AddSavingsDialog::receiveAddSavings(){
    this->ui->savingSystemLE->setText("");
    this->ui->balanceLE->setText("");
    this->show();
}
