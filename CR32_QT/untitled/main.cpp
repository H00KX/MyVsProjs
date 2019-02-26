#include "mainwindow.h"
#include <QApplication>

#include <QtPlugin>

Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(881, 501);
    w.show();

    return a.exec();
}
