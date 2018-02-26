#ifndef MYGRAPH_H
#define MYGRAPH_H

#include "data.h"

#include <stack>
#include <QDebug>
#include <QString>
#include <iostream>
#include <stdlib.h>
#include <QObject>

/*
**  实体类
** 组成图的必要结构
*/

/*
** 边
*/
class MyEdge
{
public:
    MyEdge();   // finished
    MyEdge(QString provider);   // finished

    QString provider;
    void *vex;
    MyEdge *adjlink;
};

/*
** 结点
*/

class MyVex{
public:
    MyVex();// finished
    MyVex(MyEvent* event);// finished

    addEdge(MyEdge *edge);// finished
    addEvent(MyEvent *event);// finished
    int deleteEdge(MyVex *vex);

    QString getLevels();

    QList<MyEvent *> *eventList;
    QString provider;
    QString time;
    MyEdge *firstEdge;
};
/**
 * @brief The MyGraph class
 * 图结构
 */
class MyGraph{
public:
    MyGraph();// finished

    /*
    ** @brief 通过target(Provier)来获得结点
    ** @brief 在graph_from中运行
    ** @author CaiNot
    */
    MyVex *getVex(QString target); // finished

    /*
    ** @brief 通过时间来获得结点
    ** @brief 在graph_time中运行
    ** @author CaiNot
    */
    MyVex *getVexTime(QString time); // finished

    /*
    ** @brief 重载
    ** @brief 通过time和arrange获得
    ** 时间与time一致的结点
    ** 然后获得其周围的第arrange层内的结点
    ** @author CaiNot
    */
    QMap<MyVex *,int> *getVexTime(QString time,int arrange);

    /*
    ** @brief 获得结点(某个Provider)的所有事件周围(时间意义上)
    ** @brief 的事件
    ** @author CaiNot
    */
    QList<MyEvent*> *getProviderEvent(MyVex *vex,int day);

    /*
    ** @brief 获得与结点相伴的其它节点(Provider)
    ** 获得该结点中的事件周围(时间意义上)
    ** 所有的Provider，包含其次数
    ** @author CaiNot
    */
    QMap<QString,int> *getSimilarEvent(MyVex *vex);

    int deleteVex(MyVex *vex);
    int compareTime(MyVex *vex_1,MyVex *vex_2);
    int compareTimeStr(QString time_1,QString time_2);

    addVex(MyVex *vex); // finished
    QString getTarget(MyVex *vex); // finished
    ~MyGraph();

    //private:
    QList<MyVex *> *vexList;
    void *object;

};

#endif // MYGRAPH_H
