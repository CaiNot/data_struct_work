#ifndef XMLGETTER_H
#define XMLGETTER_H
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamReader>
#include <QDebug>
#include <QString>
#include <QtXml>
#include "data.h"
#include "mygraph.h"

enum DATATYPE{
    Events,Event,System,Provider,EventID,Level,Task,Keywords,
    TimeCreated,EventRecordID,Channel,Computer,Security,Data,
    Message,Opcode,RenderingInfo
};

class XMLGetter{

public:
    int getXML(QString PATH);
    QDomElement *readXML(QDomElement *element);
    int createEvent(QDomElement *element);
    int writeXML(QString PATH,MyGraph *graph);
    ~XMLGetter();

    MyGraph *graph;


private:
    QFile *file;
    QDomDocument *xmlDoc;


    MyVex *vex;
    MyEdge *edge;
    MyEvent *event;
    MyData *data,*system_data,*event_data,*render_data;
    QList<MyVex*> *vex_list;
    QList<MyEvent*> *event_list;

    int count=0;
    int i=0;
    QString name;
    QString details;



};

#endif // XMLGETTER_H
