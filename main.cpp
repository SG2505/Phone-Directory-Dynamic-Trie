#include "mainscreen.h"
#include <QApplication>
#include <QLayout>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainscreen w;
    w.showMaximized();
    w.setMinimumWidth(1100);
    w.setMinimumHeight(660);
    w.show();
    return a.exec();
}
