#ifndef ADDSAVINGSDIALOG_H
#define ADDSAVINGSDIALOG_H

#include <QDialog>
#include "dbsetting.h"
namespace Ui {
class AddSavingsDialog;
}

class AddSavingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSavingsDialog(QWidget *parent = nullptr);
    ~AddSavingsDialog();
    void setDB(QSqlDatabase db);

private:
    Ui::AddSavingsDialog *ui;
    QSqlDatabase db;
private slots:
    void on_conformBtn_clicked();
    void on_returnBtn_clicked();
    void receiveAddSavings();
signals:
    void returnMain();
};

#endif // ADDSAVINGSDIALOG_H
