#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#include "data.h"
#include "mygraph.h"
#include "xmlgetter.h"

class MyClass{
public:
    MyClass();
//    MyGraph *createGraphByFrom(QString PATH);
    MyGraph *createGraphByTime();


    MyGraph *graph,*graph_time;
};



#endif // MYFUNCTIONS_H
