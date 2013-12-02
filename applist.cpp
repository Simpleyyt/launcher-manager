#include "applist.h"
#include "settingsdialog.h"

AppList::AppList(QWidget *parent) :
    QListWidget(parent)
{
    this->setViewMode(QListWidget::IconMode);
    this->setIconSize(QSize(64,64));
    this->setFlow(QListView::LeftToRight);
    this->setSpacing(15);
    this->setResizeMode(QListWidget::Adjust);

    initialApplications();

    connect(this,SIGNAL(itemActivated(QListWidgetItem*)),this, SLOT(itemActivatedSlot(QListWidgetItem*)));
}

void AppList::refresh()
{
    this->clear();
    initialApplications();
}

void AppList::itemActivatedSlot(QListWidgetItem *item)
{
    qDebug() << item->text() << "activated.";

    AppItem *appitem = (AppItem *)item;
    EditDialog *e = new EditDialog(appitem, this);
    if (e->exec() == QDialog::Accepted)
        this->refresh();
    //appitem->runExec();
}

void AppList::initialApplications()
{
    QDir dir(SettingsDialog::getAppPath(),"*.desktop");
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
            QFileInfo fileInfo = list.at(i);
            AppItem *appItem = new AppItem(fileInfo.absoluteFilePath());
            if (appItem->isApplication())
                this->addItem(appItem);
            else
                delete appItem;
        }
}
