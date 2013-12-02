#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include "mainwindow.h"

QString SettingsDialog::AppPath = "/usr/share/applications/";
QString SettingsDialog::Language = QLocale::system().name();
QString SettingsDialog::Theme = "elementary";
bool SettingsDialog::backup = true;

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    settings = new QSettings("SYSU", "Launcher Manager", this);

    restoreSettings();

    ui->locaEdit->setText(AppPath);
    ui->themeEdit->setText(Theme);
    ui->lanEdit->setText(Language);
    ui->backupBox->setChecked(backup);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::saveSettings()
{
    settings->setValue("system/path", ui->locaEdit->text());
    settings->setValue("system/theme", ui->themeEdit->text());
    settings->setValue("system/language", ui->lanEdit->text());
    settings->setValue("backup/enable", ui->backupBox->isChecked());
}

void SettingsDialog::restoreSettings()
{
    AppPath = settings->value("system/path", AppPath).toString();
    Theme = settings->value("system/theme", Theme).toString();
    Language = settings->value("system/language", Language).toString();
    backup = settings->value("backup/enable", backup).toBool();
}


void SettingsDialog::on_buttonBox_accepted()
{
    saveSettings();
    restoreSettings();
}

void SettingsDialog::on_clearButton_clicked()
{
    if (QMessageBox::warning(this, tr("Clear Backup"), tr("Do you want to delete all the backup ?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
    {
        QDir dir("./applications/","*.desktop_bak");
        QFileInfoList list = dir.entryInfoList();
        for (int i = 0; i < list.size(); ++i)
        {
                QString file_name = list.at(i).absoluteFilePath();
                QFile::remove(file_name);
        }
        QMessageBox::information(this, tr("Clear Backup"), tr("File delete successfully."), QMessageBox::Ok);
        MainWindow *mainwindow = (MainWindow*)this->parent();
        mainwindow->refreshList();
    }
}

void SettingsDialog::on_restoreButton_clicked()
{
    if (QMessageBox::warning(this, tr("Restore Backup"), tr("Do you want to restore all the backup ?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
    {
        QDir dir(SettingsDialog::getAppPath(),"*.desktop_bak");
        QFileInfoList list = dir.entryInfoList();
        for (int i = 0; i < list.size(); ++i)
        {
                QString backup_file_name = list.at(i).absoluteFilePath();
                QString file_name = QString(backup_file_name).remove(QRegExp("_bak$"));
                QFile::remove(file_name);
                QFile::copy(backup_file_name, file_name);
        }
        QMessageBox::information(this, tr("Restore Backup"), tr("Backup restore successfully."), QMessageBox::Ok);
        MainWindow *mainwindow = (MainWindow*)this->parent();
        mainwindow->refreshList();
    }
}
