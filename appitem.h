#ifndef APPITEM_H
#define APPITEM_H

#include <QListWidgetItem>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QDebug>
#include <QRegExp>
#include <QProcess>

#define APP_LOCATION ""

class AppItem : public QObject, public QListWidgetItem
{
    Q_OBJECT
public:
    explicit AppItem(QString filename, QListWidget *parent = 0);

    typedef QMap<QString, QString> SettingsMap;

    inline void setName(const QString &name) { settings_map["Name"] = name; }
    inline void setComment(const QString &comment) { settings_map["Comment"] = comment; }
    inline void setExec(const QString &exec) { settings_map["Exec"] = exec; }
    inline void setIconUrl(const QString &icon) { settings_map["Icon"] = icon; }
    inline void setCategories(const QString &categories) { settings_map["Categories"] = categories; }

    inline const QString getName() { return settings_map["Name"]; }
    inline const QString getComment() { return settings_map["Comment"]; }
    inline const QString getExec() { return settings_map["Exec"]; }
    inline const QString getIconUrl() { return settings_map["Icon"]; }
    inline const QString getCategories() { return settings_map["Categories"]; }
    inline const bool isApplication() { return settings_map["Type"]=="Application"; }

    void saveSettings();
    void restoreSettings();
    void runExec();
    bool remove();
    bool restoreBackup();

signals:
    
public slots:
    
private:
    QString settings_filename;
    SettingsMap settings_map;

    QString parseValue(const QString *file_content, const QString &key);
    void setValue(QString *file_content, const QString &key, const QString &value);

    QRegExp getSuitRegExp(const QString *file_content, const QString &key);
    void createNewValue(QString *file_content, const QString &key, const QString &value);
};

#endif // APPITEM_H
