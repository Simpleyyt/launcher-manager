#ifndef APPLIST_H
#define APPLIST_H

#include <QListWidget>
#include <QSettings>
#include "appitem.h"
#include "editdialog.h"

class AppList : public QListWidget
{
    Q_OBJECT
public:
    explicit AppList(QWidget *parent = 0);
    void refresh();

signals:
    
public slots:
    void itemActivatedSlot(QListWidgetItem *item);

private:
    void initialApplications();
};

#endif // APPLIST_H
