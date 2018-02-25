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
//    QString PATH="D:\\SystemXML.xml";
//    XMLGetter *getter=new XMLGetter();
//    getter->getXML(PATH);
//    MyClass *my=new MyClass();
//    my->graph=getter->graph;
//    my->createGraphByTime();

//    return 0;
    return a.exec();
}
