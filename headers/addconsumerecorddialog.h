#ifndef ADDCONSUMERECORDDIALOG_H
#define ADDCONSUMERECORDDIALOG_H

#include <QDialog>
#include "dbsetting.h"

namespace Ui
{
    class AddConsumeRecordDialog;
}

class AddConsumeRecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddConsumeRecordDialog(QWidget *parent = nullptr);
    ~AddConsumeRecordDialog();
    void setDB(QSqlDatabase db);

private slots:
    void on_conformBtn_clicked();
    void on_returnBtn_clicked();
    void on_consumeChkBox_stateChanged();
    void on_depositChkBox_stateChanged();

public slots:
    void receiveAddConsume(int user_id, QHash<QString, int> saving_system);
signals:
    void flushMainWindow();

private:
    Ui::AddConsumeRecordDialog *ui;
    int user_id;
    QHash<QString, int> saving_system;
    QSqlDatabase db;
};

#endif // ADDCONSUMERECORDDIALOG_H
