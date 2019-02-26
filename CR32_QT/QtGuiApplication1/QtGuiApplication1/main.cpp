#include "qtguiapplication1.h"
#include <QtWidgets/QApplication>

#include <QtPlugin>

//Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtGuiApplication1 w;
    w.show();


    return a.exec();
}
