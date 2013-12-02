#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include "appitem.h"
#include <QFileDialog>

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditDialog(AppItem *item, QWidget *parent = 0);
    ~EditDialog();
    
private slots:
    void on_changeIconButton_clicked();

    void on_buttonBox_accepted();

    void on_restoreButton_clicked();

    void on_iconEdit_editingFinished();

private:
    Ui::EditDialog *ui;
    AppItem *appitem;
    void updateSettings();
};

#endif // EDITDIALOG_H
