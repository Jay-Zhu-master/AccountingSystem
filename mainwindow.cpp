#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setDB(QSqlDatabase db){
    this->db = db;
}

void MainWindow::on_flushSavingsBtn_clicked(){
    this->flushSavingsTabView();
    this->flushConsumeRecordTabView();
}

void MainWindow::on_addSavingsBtn_clicked(){
    emit addSavings();
}

void MainWindow::receiveLogin(int user_id){
    this->user_id = user_id;
    this->flushSavingsTabView();
    this->flushConsumeRecordTabView();
    this->show();
}

void MainWindow::on_delSavingsBtn_clicked(){
    QSqlQuery query;
    QString sql;
    if(this->ui->savingsTabWidgets->selectedItems().length() == 0){
        QMessageBox::information(this,"提示","请选择需要删除的数据！");
        return;
    }
    for(int i = 0; i < this->ui->savingsTabWidgets->selectedItems().length(); i++){
        sql = QString("delete from user_savings where id = %1").
                arg(this->ui->savingsTabWidgets->item(1,this->ui->savingsTabWidgets->selectedItems()[i]->column())->text());
        qDebug() << sql;
        query.exec(sql);
    }
    QMessageBox::information(this,"提示","删除成功！");
    this->flushSavingsTabView();
}
void MainWindow::on_modifyBtn_clicked(){
    if(this->ui->savingsTabWidgets->selectedItems().length() == 0){
        QMessageBox::information(this,"提示","请单击选择需要修改的数据！");
        return;
    }
    if(this->ui->savingsTabWidgets->selectedItems().length() > 1){
        QMessageBox::information(this,"提示","只能选择一个修改！");
        return;
    }
    emit modifySavings(this->ui->savingsTabWidgets->item(1,this->ui->savingsTabWidgets->selectedItems()[0]->column())->text().toInt()
            ,this->ui->savingsTabWidgets->horizontalHeaderItem(this->ui->savingsTabWidgets->selectedItems()[0]->column())->text()
            ,this->ui->savingsTabWidgets->item(0,this->ui->savingsTabWidgets->selectedItems()[0]->column())->text());
}

void MainWindow::on_selectRecordBtn_clicked(){}
void MainWindow::on_addRecordBtn_clicked(){
    emit addConsume(this->user_id,this->saving_system);
}
void MainWindow::on_modifyRecordBtn_clicked(){
    QList<QTableWidgetItem*> items = this->ui->recordTableWidget->selectedItems();
    if(items.isEmpty()){
        QMessageBox::warning(this,"警告","请选择一行！");
        return;
    }
    if(items.length() > 1){
        int t = items[0]->row();
        for(int i = 1; i < items.length(); i ++){
            if(t != items[i]->row()){
                QMessageBox::warning(this,"警告","只能选择一行！");
                return;
            }
        }
    }

    emit modifyConsume(this->ui->recordTableWidget->item(items[0]->row(),5)->text().toInt(),this->saving_system);
}
void MainWindow::on_deleteRecordBtn_clicked(){}

void MainWindow::flushSavingsTabView(){
    QString sql = QString("select * from user_savings where user_id = %1 order by id asc;").arg(this->user_id);
    QSqlQuery query;
    QStringList stringList;
    this->ui->savingsTabWidgets->clear();
    this->saving_system.clear();
    qDebug() << sql;
    query.exec(sql);
    this->ui->savingsTabWidgets->setRowCount(2);
    this->ui->savingsTabWidgets->setColumnCount(0);
    while (query.next()) {
        this->saving_system.insert(query.value("saving_system").toString(),query.value("id").toInt());
        this->ui->savingsTabWidgets->setColumnCount(this->ui->savingsTabWidgets->columnCount()+1);
        stringList.append(query.value("saving_system").toString());
        this->ui->savingsTabWidgets->setHorizontalHeaderLabels(stringList);
        this->ui->savingsTabWidgets->setItem(0,this->ui->savingsTabWidgets->columnCount() - 1
                                             ,new QTableWidgetItem(query.value("balance").toString()));
        this->ui->savingsTabWidgets->setItem(1,this->ui->savingsTabWidgets->columnCount() - 1
                                             ,new QTableWidgetItem(query.value("id").toString()));
    }
    this->ui->savingsTabWidgets->hideRow(1);
}

void MainWindow::flushConsumeRecordTabView(){
    QSqlQuery query;
    QString sql;

    this->ui->recordTableWidget->clearContents();
    this->ui->recordTableWidget->setRowCount(0);
    sql = QString("SELECT id, user_id, name, saving_system, saving_system_id, consume_mode,money, detail, date_format(consume_time,'%Y/%m/%d %H:%i:%s') consume_time, create_time"
                  " FROM accounting_system.expense_calendar where user_id = %1 order by consume_time desc;").arg(this->user_id);
    qDebug() << sql;
    query.exec(sql);
    qDebug() << query.lastError().type();
    qDebug() << query.lastError().text();

    while(query.next()){
        this->ui->recordTableWidget->setRowCount(this->ui->recordTableWidget->rowCount()+1);
        this->ui->recordTableWidget->setItem(this->ui->recordTableWidget->rowCount()-1,0,new QTableWidgetItem(query.value("name").toString()));
        this->ui->recordTableWidget->setItem(this->ui->recordTableWidget->rowCount()-1,1,new QTableWidgetItem(query.value("saving_system").toString()));
        this->ui->recordTableWidget->setItem(this->ui->recordTableWidget->rowCount()-1,2,new QTableWidgetItem(QString(query.value("consume_mode").toInt() == 1 ? "-" : "+") +  query.value("money").toString()));
        this->ui->recordTableWidget->setItem(this->ui->recordTableWidget->rowCount()-1,3,new QTableWidgetItem(query.value("detail").toString()));
        this->ui->recordTableWidget->setItem(this->ui->recordTableWidget->rowCount()-1,4,new QTableWidgetItem(query.value("consume_time").toString()));
        this->ui->recordTableWidget->setItem(this->ui->recordTableWidget->rowCount()-1,5,new QTableWidgetItem(query.value("id").toString()));
    }
    this->ui->recordTableWidget->hideColumn(5);
    this->ui->recordTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->ui->recordTableWidget->horizontalHeader()->setSectionResizeMode(4,QHeaderView::ResizeToContents);
}


void MainWindow::receiveFlush(){
    this->flushSavingsTabView();
    this->flushConsumeRecordTabView();
}
