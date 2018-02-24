#include "mygraph.h"


MyGraph::MyGraph()
{
    this->vexList=new QList<MyVex *>();
    this->object=NULL;

}

MyVex *MyGraph::getVex(QString target)
{
    MyVex *vex=NULL;
    int length=this->vexList->length();
    for(int i= 0;i<length;i++){
        vex=this->vexList->at(i);
        if(target==vex->provider){
            return vex;
        }
    }
    return NULL;
}

MyVex *MyGraph::getVexTime(QString time)
{
    MyVex *vex=NULL;
    int length=this->vexList->length();
    for(int i= 0;i<length;i++){
        vex=this->vexList->at(i);
        if(time==vex->time){
            return vex;
        }
    }
    return NULL;
}

int MyGraph::compareTime(MyVex *vex_1, MyVex *vex_2)
{
    int vex_1_time=vex_1->time.toInt();
    int vex_2_time=vex_2->time.toInt();

    return vex_1_time-vex_2_time;
}

MyGraph::addVex(MyVex *vex)
{
    this->vexList->append(vex);
}

//QString MyGraph::getTarget(MyVex *vex)
//{
//    if(vex)
//    {
//        int position=vex->event->
//                system_data->getDetailByName("Provider");
//        if(position>-1)
//            return vex->event->system_data->details->at(position);
//    }
//    else return NULL;
//}



MyEdge::MyEdge()
{
    this->adjlink=NULL;
}

MyEdge::MyEdge(QString provider)
{
    this->provider=provider;
    this->adjlink=NULL;
}

MyVex::MyVex()
{
    this->eventList=new QList<MyEvent *>;
    this->firstEdge=NULL;
}

MyVex::MyVex(MyEvent *event)
{
    this->eventList=new QList<MyEvent *>;
    this->eventList->append(event);
    this->firstEdge=NULL;
}

MyVex::addEdge(MyEdge *edge)
{
    if(edge!=NULL){
        if(this->firstEdge==NULL){
            this->firstEdge=edge;
        }else{
            MyEdge *tempEdge=this->firstEdge;
            while(tempEdge->adjlink!=NULL){
                tempEdge=tempEdge->adjlink;
            }
            tempEdge->adjlink=edge;
        }
    }
}

MyVex::addEvent(MyEvent *data)
{
    this->eventList->append(data);
}
