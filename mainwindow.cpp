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
