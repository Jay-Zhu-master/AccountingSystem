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

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    int user_id;

private slots:
    void on_flushSavingsBtn_clicked();
    void on_addSavingsBtn_clicked();
    void mainWinodwResiveShow();
    void setUserId(int user_id);

signals:
    void addSavings();
};
#endif // MAINWINDOW_H
