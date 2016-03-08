#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setOrganizationName("GrodansParadisAB");
    a.setOrganizationDomain("grodansparadis.com");
    a.setApplicationName("vscpworks");
    MainWindow w;
    w.show();

    return a.exec();
}
