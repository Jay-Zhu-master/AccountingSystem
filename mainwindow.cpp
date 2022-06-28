#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

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
}

void MainWindow::on_addSavingsBtn_clicked(){
    emit addSavings();
}

void MainWindow::receiveLogin(int user_id){
    this->user_id = user_id;
    this->flushSavingsTabView();
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

void MainWindow::flushSavingsTabView(){
    QString sql = QString("select * from user_savings where user_id = %1 order by id asc;").arg(this->user_id);
    QSqlQuery query;
    QStringList stringList;
    this->ui->savingsTabWidgets->clear();
    qDebug() << sql;
    query.exec(sql);
    this->ui->savingsTabWidgets->setRowCount(2);
    this->ui->savingsTabWidgets->setColumnCount(0);
    while (query.next()) {
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

void MainWindow::receiveFlush(){
    this->flushSavingsTabView();
}
