#ifndef REGISTDIALOG_H
#define REGISTDIALOG_H

#include <QDialog>
#include "dbsetting.h"

namespace Ui {
class RegistDialog;
}

class RegistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegistDialog(QWidget *parent = nullptr);
    void setDB(QSqlDatabase db);
    ~RegistDialog();

private:
    Ui::RegistDialog *ui;
    QSqlDatabase db;
private slots:
    void on_conformBtn_clicked();
    void on_returnBtn_clicked();
public slots:
    void receiveRegist();

signals:
    void returnLogin();
};
#endif // REGISTDIALOG_H
