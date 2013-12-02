#include "editdialog.h"
#include "ui_editdialog.h"
#include <QMessageBox>
#include "applist.h"
#include "systemhelper.h"

EditDialog::EditDialog(AppItem *item, QWidget *parent) :
    QDialog(parent),
    appitem(item),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);

    this->setWindowTitle(item->getName());

    ui->nameEdit->setText(item->getName());
    ui->comEdit->setText(item->getComment());
    ui->catEdit->setText(item->getCategories());
    ui->iconEdit->setText(item->getIconUrl());
    ui->execEdit->setText(item->getExec());
    ui->titleLabel->setText("<h3>" + item->getName() + "</h3>");
    ui->icon->setPixmap(item->icon().pixmap(QSize(64,64)));
}

EditDialog::~EditDialog()
{
    delete ui;
}

void EditDialog::on_changeIconButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose An Icon"),
                                                    "/home",
                                                    tr("Image files(*.ico *.icon *.bmp *.png *.xpm *.jpg);;All files(*.*)"));
    ui->iconEdit->setText(fileName);
    QIcon icon(fileName);
    ui->icon->setPixmap(icon.pixmap(QSize(64,64)));
}

void EditDialog::on_buttonBox_accepted()
{
    updateSettings();
    QMessageBox::information(this, tr("Save Successfully"), tr("Save application successfully!"), QMessageBox::Ok);
    this->accept();
}

void EditDialog::updateSettings()
{
    appitem->setName(ui->nameEdit->text());
    appitem->setIconUrl(ui->iconEdit->text());
    appitem->setComment(ui->comEdit->text());
    appitem->setCategories(ui->catEdit->text());
    appitem->setExec(ui->execEdit->text());
    appitem->saveSettings();
}

void EditDialog::on_restoreButton_clicked()
{
    if (appitem->restoreBackup())
    {
        QMessageBox::information(this, tr("Successfully"), tr("Restore backup successfully!"), QMessageBox::Ok);
        this->close();
        AppList *applist = (AppList*)appitem->listWidget();
        applist->refresh();
    }
    else
        QMessageBox::critical(this, tr("Failed"), tr("Failed to restore backup."), QMessageBox::Ok);
}

void EditDialog::on_iconEdit_editingFinished()
{

    //Set the icon to display
    QIcon icon = SystemHelper::getSystemIcon(ui->iconEdit->text());
    ui->icon->setPixmap(icon.pixmap(QSize(64,64)));
}
