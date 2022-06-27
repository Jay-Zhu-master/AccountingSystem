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
    int user_id;
private slots:
    void on_conformBtn_clicked();
    void on_returnBtn_clicked();
    void receiveAddSavings();
    void setUserId(int user_id);
signals:
    void flushSavings();
};

#endif // ADDSAVINGSDIALOG_H
