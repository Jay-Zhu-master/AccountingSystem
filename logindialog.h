#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "dbsetting.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    void setDB(QSqlDatabase db);

private:
    Ui::LoginDialog *ui;
    QSqlDatabase db;
private slots:
    void receiveReturn();
    void on_loginBtn_clicked();
    void on_registBtn_clicked();
    void on_quitBtn_clicked();

signals:
    void loginSuccess();
    void quit();
    void registSignal();
};

#endif // LOGINDIALOG_H
