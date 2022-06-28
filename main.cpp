#include "mainwindow.h"
#include "dbsetting.h"
#include "logindialog.h"
#include "registdialog.h"
#include "addsavingsdialog.h"
#include "modifysavingsdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWd;
    LoginDialog loginDig;
    RegistDialog registDig;
    AddSavingsDialog addSavingsDig;
    ModifySavingsDialog modifySavingsDig;
    DBSetting db;

    mainWd.setDB(db.getDb());
    registDig.setDB(db.getDb());
    loginDig.setDB(db.getDb());
    modifySavingsDig.setDb(db.getDb());

    QObject::connect(&loginDig,SIGNAL(loginSuccess(int)),&mainWd,SLOT(receiveLogin(int)));
    QObject::connect(&loginDig,SIGNAL(registSignal()),&registDig,SLOT(receiveRegist()));
    QObject::connect(&registDig,SIGNAL(returnLogin()),&loginDig,SLOT(receiveReturn()));
    QObject::connect(&loginDig,SIGNAL(quit()),&a,SLOT(quit()));
    QObject::connect(&mainWd,SIGNAL(addSavings()),&addSavingsDig,SLOT(receiveAdd()));
    QObject::connect(&loginDig,SIGNAL(loginSuccess(int)),&addSavingsDig,SLOT(setUserId(int)));
    QObject::connect(&addSavingsDig,SIGNAL(flushSavings()),&mainWd,SLOT(receiveFlush()));
    QObject::connect(&modifySavingsDig,SIGNAL(flushSavings()),&mainWd,SLOT(receiveFlush()));
    QObject::connect(&mainWd,SIGNAL(modifySavings(int,QString,QString)),&modifySavingsDig,SLOT(receiveModify(int,QString,QString)));
    loginDig.show();
    return a.exec();
}

