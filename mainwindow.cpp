#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QDebug>
#include <QDir>
#include <QInputDialog>
#include <QMessageBox>
#include "settingsdialog.h"
#include "aboutdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sd = new SettingsDialog(this);
    applist = new AppList(this);
    applist->setMovement(QListWidget::Static);
    this->setCentralWidget(applist);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAdd_triggered()
{
    QString filename;
    while (filename = QInputDialog::getText(this,tr("Input a file name"), tr("Input a file name")), !filename.isNull())
    {
        filename = SettingsDialog::getAppPath() + filename + ".desktop";
        QFile file(filename);
        if (!file.exists())
        {
            AppItem *item = new AppItem(filename, applist);
            EditDialog editDialog(item, this);
            if (editDialog.exec() == QDialog::Accepted)
                refreshList();
            break;
        }
        else
        {
            QMessageBox::critical(this, tr("File Exists"), tr("The desktop file already exist. Please input the other one."), QMessageBox::Ok);
        }
    }
}

void MainWindow::on_actionEdit_triggered()
{
    AppItem *item = (AppItem*)applist->currentItem();
    EditDialog editDialog(item, this);
    if (editDialog.exec() == QDialog::Accepted)
        refreshList();
}

void MainWindow::on_actionRun_triggered()
{
    AppItem *item = (AppItem*)applist->currentItem();
    item->runExec();
}

void MainWindow::on_actionDelete_triggered()
{
    AppItem *item = (AppItem*)applist->currentItem();
    if (QMessageBox::warning(this, tr("Delete File"), tr("Do you want to delete the file %1 ?").arg(item->text()), QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
    {
        if (item->remove())
        {
            QMessageBox::information(this, tr("Delete File"), tr("File delete successfully."), QMessageBox::Ok);
            refreshList();
        }
        else
            QMessageBox::critical(this, tr("Delete File"), tr("Failed to delete file."), QMessageBox::Ok);
    }
}

void MainWindow::on_actionRefresh_triggered()
{
    refreshList();
}

void MainWindow::on_actionSettings_triggered()
{
    if (sd->exec() == QDialog::Accepted)
        refreshList();
}

void MainWindow::refreshList()
{
    applist->refresh();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog about_dialog(this);
    about_dialog.exec();
}
