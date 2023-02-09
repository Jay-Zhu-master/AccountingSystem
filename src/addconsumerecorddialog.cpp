#include "addconsumerecorddialog.h"
#include "ui_addconsumerecorddialog.h"
#include <QMessageBox>

AddConsumeRecordDialog::AddConsumeRecordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddConsumeRecordDialog)
{
    ui->setupUi(this);
}

AddConsumeRecordDialog::~AddConsumeRecordDialog()
{
    delete ui;
}

// 设置数据库
void AddConsumeRecordDialog::setDB(QSqlDatabase db){
    this->db = db;
}

//收到新增记录信号
void AddConsumeRecordDialog::receiveAddConsume(int user_id,QHash<QString,int> saving_system){
    //初始化界面
    this->setWindowModality(Qt::ApplicationModal);
    this->ui->nameLE->clear();
    this->ui->savingSystemComBox->clear();
    this->ui->moneyLE->clear();
    this->ui->detailTXE->clear();
    this->ui->consumeChkBox->setCheckState(Qt::CheckState::Checked);
    this->ui->depositChkBox->setCheckState(Qt::CheckState::Unchecked);
    this->user_id = user_id;
    this->saving_system = saving_system;
    this->ui->savingSystemComBox->addItems(this->saving_system.keys());
    this->ui->savingSystemComBox->insertItem(0,"<请选择消费系统>");
    this->ui->savingSystemComBox->setCurrentIndex(0);
    this->ui->consumeTimeTME->setDateTime(QDateTime::currentDateTime());
    this->show();
}

//点击确认按钮
void AddConsumeRecordDialog::on_conformBtn_clicked(){
    QString sql;
    QSqlQuery query;
    static QRegularExpression rx("^[0-9]+(.[0-9]{1,2})?$");
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
    if(! rx.match(this->ui->moneyLE->text()).hasMatch()){
        QMessageBox::warning(this,"警告","金额格式不正确!");
        return;
    }
//    qDebug() << this->ui->detailTXE->document()->toRawText();
    if(this->ui->detailTXE->document()->toRawText() == ""){
        QMessageBox::warning(this,"警告","请输入消费明细!");
        return;
    }
    sql = QString("INSERT INTO expense_calendar (user_id, name, saving_system, saving_system_id, consume_mode, money, detail, consume_time) "
          "VALUES(%1, '%2', '%3', %4, %5, %6, '%7','%8');")
            .arg(this->user_id).arg(this->ui->nameLE->text())
            .arg(this->ui->savingSystemComBox->currentText(),this->saving_system.value(this->ui->savingSystemComBox->currentText()))
            .arg(this->ui->consumeChkBox->checkState() == Qt::CheckState::Checked ? "1":"2").arg(this->ui->moneyLE->text().toDouble())
            .arg(this->ui->detailTXE->document()->toRawText(),this->ui->consumeTimeTME->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    qDebug() << sql;
    if(!DBSetting::execSql(this,query,sql,"警告","增加失败，错误代码 : ")){
        return;
    }
    sql = QString("update user_savings set balance = CONVERT(balance %1 %2,DECIMAL(10,2)) where id = %3")
            .arg(this->ui->consumeChkBox->checkState() == Qt::CheckState::Checked? "-":"+")
            .arg(this->ui->moneyLE->text(),this->saving_system.value(this->ui->savingSystemComBox->currentText()));
    qDebug() << sql;
    if(!DBSetting::execSql(this,query,sql,"警告","增加失败，错误代码 : ")){
        return;
    }
    QMessageBox::information(this,"提示","添加成功！");
    emit flushMainWindow();
    this->hide();
}

//点击返回按钮
void AddConsumeRecordDialog::on_returnBtn_clicked(){
    this->hide();
}

//下面两个函数确保勾选框只能选中一个
void AddConsumeRecordDialog::on_consumeChkBox_stateChanged(){
//    qDebug() << "clicked";
    if(this->ui->consumeChkBox->checkState() == Qt::CheckState::Checked){
        this->ui->depositChkBox->setCheckState(Qt::CheckState::Unchecked);
    }else{
        this->ui->depositChkBox->setCheckState(Qt::CheckState::Checked);
    }

}
void AddConsumeRecordDialog::on_depositChkBox_stateChanged(){
//    qDebug() << "clicked";
    if(this->ui->depositChkBox->checkState() == Qt::CheckState::Checked){
        this->ui->consumeChkBox->setCheckState(Qt::CheckState::Unchecked);
    }else{
        this->ui->consumeChkBox->setCheckState(Qt::CheckState::Checked);
    }
}
