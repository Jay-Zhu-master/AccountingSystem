#include "mainwindow.h"
#include "dbsetting.h"
#include "logindialog.h"
#include "registdialog.h"
#include "addsavingsdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWd;
    LoginDialog loginDig;
    RegistDialog registDig;
    AddSavingsDialog addSavingsDig;
    DBSetting db;

    mainWd.setDB(db.getDb());
    registDig.setDB(db.getDb());
    loginDig.setDB(db.getDb());

    QObject::connect(&loginDig,SIGNAL(loginSuccess()),&mainWd,SLOT(mainWinodwResiveShow()));
    QObject::connect(&loginDig,SIGNAL(registSignal()),&registDig,SLOT(receiveRegist()));
    QObject::connect(&registDig,SIGNAL(returnLogin()),&loginDig,SLOT(receiveReturn()));
    QObject::connect(&loginDig,SIGNAL(quit()),&a,SLOT(quit()));
    QObject::connect(&mainWd,SIGNAL(addSavings()),&addSavingsDig,SLOT(receiveAddSavings()));
    loginDig.show();
    return a.exec();
}

