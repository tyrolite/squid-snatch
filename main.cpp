#include <QtGui/QApplication>
#include "MainCtrl.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainCtrl mc;
    mc.begin();;

    return a.exec();
}
