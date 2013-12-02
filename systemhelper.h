#ifndef SYSTEMHELPER_H
#define SYSTEMHELPER_H

#include <QIcon>
#include <QSettings>

class SystemHelper
{
public:
    SystemHelper();
    static QIcon getSystemIcon (QString icon_name);
};

#endif // SYSTEMHELPER_H
