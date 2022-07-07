#include "modifyconsumerecorddialog.h"
#include "ui_modifyconsumerecorddialog.h"
#include <QMessageBox>

ModifyConsumeRecordDialog::ModifyConsumeRecordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyConsumeRecordDialog)
{
    ui->setupUi(this);
}

ModifyConsumeRecordDialog::~ModifyConsumeRecordDialog()
{
    delete ui;
}

void ModifyConsumeRecordDialog::setDB(QSqlDatabase db){
    this->db = db;
}

void ModifyConsumeRecordDialog::receiveModifyConsume(int recordId,QHash<QString,int> saving_system){
    QSqlQuery query;
    QString sql = QString("SELECT id, user_id, name, saving_system, saving_system_id, consume_mode,money, detail, consume_time, create_time"
                          " FROM expense_calendar where id = %1;").arg(recordId);
    qDebug() << sql;
    this->setWindowModality(Qt::ApplicationModal);
    this->recordId = recordId;
    this->saving_system = saving_system;
    query.exec(sql);
    query.next();

    this->savingSystemId = query.value("saving_system_di").toInt();
    this->ui->nameLE->setText(query.value("name").toString());
    this->ui->savingSystemComBox->addItems(saving_system.keys());
    this->ui->savingSystemComBox->setCurrentText(query.value("saving_system").toString());
    this->ui->moneyLE->setText(query.value("money").toString());
    this->ui->detailTXE->setText(query.value("detail").toString());
    if(query.value("consume_mode").toString() == "1"){
        this->ui->consumeChkBox->setCheckState(Qt::CheckState::Checked);
        this->ui->depositChkBox->setCheckState(Qt::CheckState::Unchecked);
    }else{
        this->ui->consumeChkBox->setCheckState(Qt::CheckState::Unchecked);
        this->ui->depositChkBox->setCheckState(Qt::CheckState::Checked);
    }
    this->ui->consumeTimeTME->setDateTime(query.value("consume_time").toDateTime());

    this->show();
}

void ModifyConsumeRecordDialog::on_conformBtn_clicked(){
    QString sql;
    QSqlQuery query;
    QRegExp rx("^[0-9]+(.[0-9]{1,2})?$");
    if(this->ui->nameLE->text() == ""){
        QMessageBox::warning(this,"警告","请输入消费名称！");
        return;
    }
    if(!this->saving_system.contains(this->ui->savingSystemComBox->currentText())){
        QMessageBox::warning(this,"警告","请选择消费系统！");
        return;
    }
    if(this->ui->moneyLE->text() == ""){
        QMessageBox::warning(this,"警告","请输入消费金额！");
        return;
    }
    if(! rx.exactMatch(this->ui->moneyLE->text())){
        QMessageBox::warning(this,"警告","金额格式不正确!");
        return;
    }
    qDebug() << this->ui->detailTXE->document()->toRawText();
    if(this->ui->detailTXE->document()->toRawText() == ""){
        QMessageBox::warning(this,"警告","请输入消费明细!");
        return;
    }

    sql = QString("SELECT id, user_id, name, saving_system, saving_system_id, consume_mode,money, detail, consume_time, create_time"
                          " FROM expense_calendar where id = %1;").arg(recordId);
    qDebug() << sql;

    query.exec(sql);
    query.next();

    sql = QString("update user_savings set balance = CONVERT(balance %1 %2,DECIMAL(10,2)) where id = %3")
            .arg(query.value("consume_mode").toString() == "1" ? "+":"-")
            .arg(query.value("money").toString())
            .arg(query.value("saving_system_id").toString());

    qDebug() << sql;

    query.exec(sql);

    sql = QString("update expense_calendar set name = '%1', saving_system = '%2', "
                  "saving_system_id = %3, consume_mode = %4, money = %5, detail = '%6', consume_time = '%7' where id = %8")
            .arg(this->ui->nameLE->text())
            .arg(this->ui->savingSystemComBox->currentText())
            .arg(this->saving_system.value(this->ui->savingSystemComBox->currentText()))
            .arg(this->ui->consumeChkBox->checkState() == Qt::CheckState::Checked ? "1":"2")
            .arg(this->ui->moneyLE->text().toDouble())
            .arg(this->ui->detailTXE->document()->toRawText())
            .arg(this->ui->consumeTimeTME->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
            .arg(this->recordId);
    qDebug() << sql;
    query.exec(sql);
    sql = QString("update user_savings set balance = CONVERT(balance %1 %2,DECIMAL(10,2)) where id = %3")
            .arg(this->ui->consumeChkBox->checkState() == Qt::CheckState::Checked? "-":"+")
            .arg(this->ui->moneyLE->text())
            .arg(this->saving_system.value(this->ui->savingSystemComBox->currentText()));
    qDebug() << sql;
    query.exec(sql);
    QMessageBox::information(this,"提示","修改成功！");
    emit flushMainWindow();
    this->hide();
}

void ModifyConsumeRecordDialog::on_returnBtn_clicked(){
    this->hide();
}


void ModifyConsumeRecordDialog::on_consumeChkBox_stateChanged(){
    qDebug() << "clicked";
    if(this->ui->consumeChkBox->checkState() == Qt::CheckState::Checked){
        this->ui->depositChkBox->setCheckState(Qt::CheckState::Unchecked);
    }else{
        this->ui->depositChkBox->setCheckState(Qt::CheckState::Checked);
    }

}
void ModifyConsumeRecordDialog::on_depositChkBox_stateChanged(){
    qDebug() << "clicked";
    if(this->ui->depositChkBox->checkState() == Qt::CheckState::Checked){
        this->ui->consumeChkBox->setCheckState(Qt::CheckState::Unchecked);
    }else{
        this->ui->consumeChkBox->setCheckState(Qt::CheckState::Checked);
    }
}
