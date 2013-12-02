#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "applist.h"
#include "appitem.h"
#include "settingsdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void refreshList();
    
private slots:
    void on_actionAdd_triggered();

    void on_actionEdit_triggered();

    void on_actionRun_triggered();

    void on_actionDelete_triggered();

    void on_actionRefresh_triggered();

    void on_actionSettings_triggered();


    void on_actionExit_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    AppList *applist;
    AppItem *appitem;
    SettingsDialog *sd;
};

#endif // MAINWINDOW_H
