#include "mainscene.h"
#include "startscene.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    startscene ww;
    ww.show();
    return a.exec();
}
