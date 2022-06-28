#ifndef MODIFYSAVINGSDIALOG_H
#define MODIFYSAVINGSDIALOG_H

#include <QDialog>
#include "dbsetting.h"
namespace Ui {
class ModifySavingsDialog;
}

class ModifySavingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifySavingsDialog(QWidget *parent = nullptr);
    ~ModifySavingsDialog();
    void setDb(QSqlDatabase db);


private:
    Ui::ModifySavingsDialog *ui;
    QSqlDatabase db;
    QString savingsSystem;
    QString balance;
    int saving_id;


private slots:
    void receiveModify(int saving_id,QString savingsSystem,QString balance);
    void on_conformBtn_clicked();
    void on_returnBtn_clicked();

signals:
    void flushSavings();
};

#endif // MODIFYSAVINGSDIALOG_H
