#ifndef MODIFYCONSUMERECORDDIALOG_H
#define MODIFYCONSUMERECORDDIALOG_H

#include <QDialog>
#include "dbsetting.h"

namespace Ui {
class ModifyConsumeRecordDialog;
}

class ModifyConsumeRecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyConsumeRecordDialog(QWidget *parent = nullptr);
    ~ModifyConsumeRecordDialog();
    void setDB(QSqlDatabase db);

private:
    Ui::ModifyConsumeRecordDialog *ui;
    QSqlDatabase db;
    int recordId;
    int savingSystemId;
    QHash<QString,int> saving_system;

private slots:
    void on_conformBtn_clicked();
    void on_returnBtn_clicked();
    void on_consumeChkBox_stateChanged();
    void on_depositChkBox_stateChanged();
public slots:
    void receiveModifyConsume(int recordId,QHash<QString,int> saving_system);
signals:
    void flushMainWindow();
};

#endif // MODIFYCONSUMERECORDDIALOG_H
