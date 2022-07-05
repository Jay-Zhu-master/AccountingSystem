#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbsetting.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setDB(QSqlDatabase db);
    void flushSavingsTabView();
    void flushConsumeRecordTabView();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    int user_id;
    QHash<QString,int> saving_system;

private slots:
    void on_flushSavingsBtn_clicked();
    void on_addSavingsBtn_clicked();
    void on_delSavingsBtn_clicked();
    void on_modifyBtn_clicked();
    void on_selectRecordBtn_clicked();
    void on_addRecordBtn_clicked();
    void on_modifyRecordBtn_clicked();
    void on_deleteRecordBtn_clicked();
public slots:
    void receiveLogin(int user_id);
    void receiveFlush();

signals:
    void addSavings();
    void modifySavings(int saving_id,QString savingsSystem,QString balance);
    void addConsume(int user_id,QHash<QString,int> saving_system);
    void modifyConsume(int recordId,QHash<QString,int> saving_system);
};
#endif // MAINWINDOW_H
