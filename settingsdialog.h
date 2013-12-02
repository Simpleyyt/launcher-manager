#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    static QString getAppPath() { return AppPath; }
    static QString getLanguage() { return Language; }
    static QString getTheme() { return Theme; }
    static bool isBackup() { return backup; }

private slots:
   void on_buttonBox_accepted();

   void on_clearButton_clicked();

   void on_restoreButton_clicked();

private:
    Ui::SettingsDialog *ui;
    QSettings *settings;

    static QString AppPath;
    static QString Language;
    static QString Theme;
    static bool backup;

    void saveSettings();
    void restoreSettings();
};

#endif // SETTINGSDIALOG_H
