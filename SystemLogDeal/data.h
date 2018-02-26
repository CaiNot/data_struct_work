#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QList>
#include <stdlib.h>
#include <iostream>

/*
** 实体类，储存数据信息
*/


/*
** 储存一个事件中的信息
*/
class MyData{
public:
    MyData();
    MyData(QString id); // finished

    setID(QString id); // finished

    addName(QString name); // finished
    addDetails(QString detail); // finished

    /*
    ** 在names的list里面寻找name
    ** 找到了name则返回它所在的位置
    ** 没有找到返回-1
    ** 此位置与details的list的位置相对应
    */
    int getDetailByNameInt(QString name);

    /*
    **  在names的list寻找name
    ** 找到了name则返回它所对应的detail
    ** 否则返回NULL
    */
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

    /*
    ** 转换时间的格式
    ** 将this->time修改为转换后的格式
    ** 返回修改后的格式
    */
    QString changeTime();
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
