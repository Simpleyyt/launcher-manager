#include "systemhelper.h"
#include <QFile>
#include "settingsdialog.h"

SystemHelper::SystemHelper()
{
}

QIcon SystemHelper::getSystemIcon(QString icon_name)
{
    QIcon::setThemeName(SettingsDialog::getTheme());
    QIcon icon = QIcon::fromTheme(icon_name);
    if (icon.isNull() && QFile::exists(icon_name))
        icon.addFile(icon_name);
    if (icon.isNull())
        icon = QIcon::fromTheme("application-default-icon");
    return icon;
}
