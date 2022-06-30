#include "mainwindow.h"
#include "dbsetting.h"
#include "logindialog.h"
#include "registdialog.h"
#include "addsavingsdialog.h"
#include "modifysavingsdialog.h"
#include "addconsumerecorddialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWd;
    LoginDialog loginDig;
    RegistDialog registDig;
    AddSavingsDialog addSavingsDig;
    ModifySavingsDialog modifySavingsDig;
    AddConsumeRecordDialog addConsumeRecordDig;
    DBSetting db;

    mainWd.setDB(db.getDb());
    registDig.setDB(db.getDb());
    loginDig.setDB(db.getDb());
    modifySavingsDig.setDb(db.getDb());

    QObject::connect(&loginDig,&LoginDialog::loginSuccess,&mainWd,&MainWindow::receiveLogin);
    QObject::connect(&loginDig,&LoginDialog::registSignal,&registDig,&RegistDialog::receiveRegist);
    QObject::connect(&registDig,&RegistDialog::returnLogin,&loginDig,&LoginDialog::receiveReturn);
    QObject::connect(&loginDig,&LoginDialog::quit,&a,&QApplication::quit);
    QObject::connect(&mainWd,&MainWindow::addSavings,&addSavingsDig,&AddSavingsDialog::receiveAdd);
    QObject::connect(&loginDig,&LoginDialog::loginSuccess,&addSavingsDig,&AddSavingsDialog::setUserId);
    QObject::connect(&addSavingsDig,&AddSavingsDialog::flushMainWindow,&mainWd,&MainWindow::receiveFlush);
    QObject::connect(&modifySavingsDig,&ModifySavingsDialog::flushMainWindow,&mainWd,&MainWindow::receiveFlush);
    QObject::connect(&mainWd,&MainWindow::modifySavings,&modifySavingsDig,&ModifySavingsDialog::receiveModify);
    QObject::connect(&mainWd,&MainWindow::AddConsume,&addConsumeRecordDig,&AddConsumeRecordDialog::receiveAddConsume);
    QObject::connect(&addConsumeRecordDig,&AddConsumeRecordDialog::flushMainWindow,&mainWd,&MainWindow::receiveFlush);
    loginDig.show();
    return a.exec();
}

