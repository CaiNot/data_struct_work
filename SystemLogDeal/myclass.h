#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#include "data.h"
#include "mygraph.h"
#include "xmlgetter.h"

class MyClass{
public:
    MyClass();

    /*
    ** 创建时间关系图
    ** 前提：this->graph含有创建时间关系图所需要的信息
    */
    MyGraph *createGraphByTime();


    MyGraph *graph,*graph_time;
};



#endif // MYFUNCTIONS_H
