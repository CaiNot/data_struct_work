#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QList>
#include <stdlib.h>
#include <iostream>

/*
** Finished
*/

class MyData{
public:
    MyData();
    MyData(QString id); // finished

    setID(QString id); // finished

    addName(QString name); // finished
    addDetails(QString detail); // finished
    int getDetailByNameInt(QString name);
    QString getDetailByNameString(QString name);

    ~MyData();


    QString id;
    QList<QString> *names;
    QList<QString> *details;
};



class MyEvent{
public:
    MyEvent(); // finished

    setEventData(MyData *event); // finished
    setSystemData(MyData *system_data); //finished
    setTime(QString time); // finished
    changeTime();
    setRecordID(QString id); // finished

    ~MyEvent();


    QString time;
    QString record_id;

    MyData *event_data;
    MyData  *system_data;
    MyData *render_data;
    MyEvent *next_event;
};

#endif // DATA_H
