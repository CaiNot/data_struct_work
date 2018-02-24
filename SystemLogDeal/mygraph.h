﻿#ifndef MYGRAPH_H
#define MYGRAPH_H

#include "data.h"

#include <stack>
#include <QDebug>
#include <QString>
#include <iostream>
#include <stdlib.h>
#include <QObject>


class MyEdge
{
public:
    MyEdge();   // finished
    MyEdge(QString provider);   // finished

    QString provider;
    void *vex;
    MyEdge *adjlink;
};

class MyVex{
public:
    MyVex();// finished
    MyVex(MyEvent* event);// finished

    addEdge(MyEdge *edge);// finished
    addEvent(MyEvent *event);// finished

    QList<MyEvent *> *eventList;
    QString provider;
    QString time;
    MyEdge *firstEdge;
};



class MyGraph{
public:
    MyGraph();// finished

    MyVex *getVex(QString target); // finished
    MyVex *getVexTime(QString time); // finished
    int compareTime(MyVex *vex_1,MyVex *vex_2);
    addVex(MyVex *vex); // finished
    QString getTarget(MyVex *vex); // finished
    ~MyGraph();

//private:
    QList<MyVex *> *vexList;
    void *object;

};

#endif // MYGRAPH_H
