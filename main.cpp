
#include <QApplication>
#include "bookmark.h"
#include "tray.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    Tray t;
    return a.exec();
}
