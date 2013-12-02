#include <QtGui/QApplication>
#include <QTranslator>
#include <QDebug>
#include <QLocale>
#include <QGtkStyle>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("gtk");
    QTranslator qtTranslator;
    qtTranslator.load( QLocale::system().name(),":/resource/lang");
    a.installTranslator(&qtTranslator);
    MainWindow w;
    w.show();

    return a.exec();
}
