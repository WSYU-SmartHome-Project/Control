#include "mainwindow.h"
#include <QApplication>
#include "connect.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connect w;
    w.show();

    return a.exec();
}
