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
    int getUserId();

private:
    Ui::LoginDialog *ui;
    QSqlDatabase db;
    int user_id;
private slots:
    void on_loginBtn_clicked();
    void on_registBtn_clicked();
public slots:
    void receiveReturn();
    void on_quitBtn_clicked();

signals:
    void loginSuccess(int user_id);
    void quit();
    void registSignal();
};

#endif // LOGINDIALOG_H
