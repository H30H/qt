#include "mainwindow.h"
#include "mywindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    myWindow w;
    w.resize(600, 600);
    w.show();
    return a.exec();
}
