#include "mainwindow.h"
#include"dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
    dialog dig;
    dig.show();
    return a.exec();
}
