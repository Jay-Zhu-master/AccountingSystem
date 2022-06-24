#include "mainwindow.h"
#include "ui_mainwindow.h"

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

}

void MainWindow::on_addSavingsBtn_clicked(){
    emit addSavings();
}

void MainWindow::mainWinodwResiveShow(){
    this->show();
}
void MainWindow::setUserId(int user_id){
    qDebug() << user_id;
    this->user_id = user_id;
}

void MainWindow::flushSavingsTabView(){
    QString sql = QString("select * from user_savings where user_id = %1 order by id asc;").arg(this->user_id);
    QSqlQuery query;
    this->ui->saingsTabView->clearSpans();
    query.exec(sql);
}
