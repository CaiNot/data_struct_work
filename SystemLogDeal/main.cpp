#include "mainwindow.h"
#include <QApplication>
#include "xmlgetter.h"
#include "myclass.h"
#include "mygraph.h"
#include "data.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
