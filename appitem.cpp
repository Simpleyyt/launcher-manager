#include "appitem.h"
#include "systemhelper.h"
#include "settingsdialog.h"

AppItem::AppItem(QString filename, QListWidget *parent) :
    QListWidgetItem(parent), settings_filename(filename)
{
    //Set the text to display.
    this->restoreSettings();
    this->setText(settings_map["Name"]);

    //Set the icon to display
    QIcon icon = SystemHelper::getSystemIcon(this->getIconUrl());
    this->setIcon(icon);

    //Set the size.
    this->setTextAlignment(Qt::AlignCenter);
    this->setSizeHint (QSize(100,100));
}

void AppItem::saveSettings()
{
    //To read the file content and change it.
    QFile *file = new QFile(settings_filename);
    bool isfileExist = file->exists();
    if(!file->open(QIODevice::ReadOnly)){
        qDebug() << "Open File:" + settings_filename + " Failed!" << endl;
    }
    QTextStream *stream = new QTextStream(file);
    stream->setCodec("uft-8");
    QString content = stream->readAll();
    qDebug() << "******Begin write file:" << settings_filename << "******" << endl;
    setValue(&content, "Categories", settings_map["Categories"]);
    setValue(&content, "Type", "Application");
    setValue(&content, "Exec", settings_map["Exec"]);
    setValue(&content, "Icon", settings_map["Icon"]);
    setValue(&content, "Comment", settings_map["Comment"]);
    setValue(&content, "Name", settings_map["Name"]);
    qDebug() << "******End write file:" << settings_filename << "******" <<endl;

    delete stream;
    file->close();
    delete file;

    if (SettingsDialog::isBackup())
    {
        //To backup the desktop file.
        if ( !QFile::exists(settings_filename+"_bak") && isfileExist)
            QFile::rename(settings_filename, settings_filename+"_bak");
        else
            QFile::remove(settings_filename);
    }

    //To save the file.
    file = new QFile(settings_filename);
    if(!file->open(QIODevice::WriteOnly)){
        qDebug() << "Open File:" + settings_filename + " Failed!" << endl;
    }
    stream = new QTextStream(file);
    stream->setCodec("uft-8");
    *stream << content;
    stream->flush();
    delete stream;
    file->close();
    delete file;
}

void AppItem::restoreSettings()
{
    //To parse the file content.
    QFile *file = new QFile(settings_filename);
    if(!file->open(QIODevice::ReadOnly))
    {
        qDebug() << "Open File:" + settings_filename + " Failed!" << endl;
    }
    QTextStream *stream = new QTextStream(file);
    stream->setCodec("uft-8");
    QString content = stream->readAll();

    qDebug() << "******Begin parse file:" << settings_filename << "******" << endl;
    settings_map["Name"] = parseValue(&content, "Name");
    settings_map["Comment"] = parseValue(&content, "Comment");
    settings_map["Icon"] = parseValue(&content, "Icon");
    settings_map["Exec"] = parseValue(&content, "Exec");
    settings_map["Categories"] = parseValue(&content, "Categories");
    settings_map["Type"] = parseValue(&content, "Type");
    qDebug() << "******End parse file:" << settings_filename << "******" <<endl;

    delete stream;
    file->close();
    delete file;
}

QString AppItem::parseValue(const QString *file_content, const QString &key)
{
    qDebug() << "To match key:" << key << "...";

    QString value = "";

    QRegExp rx = getSuitRegExp(file_content, key);

    int pos = file_content->indexOf(rx);
    if ( pos >= 0 )
    {
        qDebug() << "Matched";
        qDebug() << "Matched String:" << rx.cap(0);

        value = rx.cap(2);
    }
    else
    {
        qDebug() << "No match";
    }
    qDebug() << "The value of key:" << key << " is " << value << endl;

    return value;
}

void AppItem::setValue(QString *file_content, const QString &key, const QString &value)
{
    qDebug() << "To write key:" << key << "...";

    QRegExp rx = getSuitRegExp(file_content,key);

    int pos = file_content->indexOf(rx);
    if ( pos >= 0 )
    {
        qDebug() << "Matched";
        qDebug() << "Matched String:" << rx.cap(0);
        qDebug() << "Change to:" << rx.cap(1)+"="+value;

        QString preValue = rx.cap(2);

        //Renew the key-value
        if (preValue != value)
        {
            file_content->replace(rx,"\\1="+value);

            qDebug() << "The value of key:" << key << " is " << value;
        }
        else
        {
            qDebug() << "Value not change";
        }
    }
    else
    {
        qDebug() << "No match";
        createNewValue(file_content, key, value);
    }



}

QRegExp AppItem::getSuitRegExp(const QString *file_content, const QString &key)
{
    //To get the suitable RegExp
    QString pattern_default("(" + key + ")=(.*)(?=\n|$)");
    QString pattern_zhCN("(" + key + "\\[" + SettingsDialog::getLanguage() + "\\])=(.*)(?=\n|$)");
    QRegExp rx(pattern_zhCN);
    rx.setMinimal (true);
    if (file_content->indexOf(rx) < 0)
        rx.setPattern(pattern_default);
    return rx;
}

void AppItem::createNewValue(QString *file_content, const QString &key, const QString &value)
{
    qDebug() << "To create new KeyValue";
    QString desktop_entry = "[Desktop Entry]";
    int pos = file_content->indexOf(desktop_entry);
    if (pos >=0 )
    {
        qDebug() << "Found " << desktop_entry;
        pos += desktop_entry.length();
    }
    else
    {
        qDebug() << desktop_entry << " no found" << endl
                 << "To create " << desktop_entry;
        file_content->insert(0,desktop_entry + "\n");
        pos = desktop_entry.length();
    }
    if (!value.isNull() && !value.isEmpty())
        file_content->insert(pos, "\n" + key + "=" + value);
}

bool AppItem::restoreBackup()
{
    if ( QFile::exists(settings_filename+"_bak") )
    {
        return QFile::remove(settings_filename) & QFile::copy(settings_filename+"_bak", settings_filename);
    }
    return false;
}

void AppItem::runExec()
{
    QProcess *process = new QProcess;
    qDebug() << settings_map["Exec"];
    process->start(settings_map["Exec"]);
}

bool AppItem::remove()
{
    qDebug() << "Remove application: " << settings_filename;
    return QFile::remove(settings_filename);
}
