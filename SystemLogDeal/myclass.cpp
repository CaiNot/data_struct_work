#include "myclass.h"


MyClass::MyClass()
{
    this->graph=NULL;
    this->graph_time=new MyGraph();
}



MyGraph *MyClass::createGraphByTime()
{
    int graphLength=this->graph->vexList->length(),graph_time_length=0;
    int vexLength=0,timeCompare=0;

    MyVex *vex=NULL,*vex_temp=NULL,*vex_in_list=NULL;
    MyEdge *edge=NULL,*edge_temp=NULL;
    MyEvent *event=NULL,*event_temp=NULL;

    for(int i=0;i<graphLength;i++){
        vex=this->graph->vexList->at(i);
        vexLength=vex->eventList->length();

        for(int j=0;j<vexLength;j++){
            event=vex->eventList->at(j);
            event->changeTime();
            vex_temp=this->graph_time->getVexTime(event->time);
            if(vex_temp==NULL){
                vex_temp=new MyVex();
                vex_temp->addEvent(event);
                vex_temp->time=event->time;
                graph_time_length=this->graph_time->vexList->length();

                for(int x=0;x<graph_time_length;x++){
                    vex_in_list=graph_time->vexList->at(x);

                    timeCompare=graph_time->compareTime(vex_in_list,vex_temp);

                    if(-5<=timeCompare&&timeCompare<=5){
                        edge=new MyEdge();
                        edge->vex=vex_temp;
                        vex_in_list->addEdge(edge);

                        edge=new MyEdge();
                        edge->vex=vex_in_list;
                        vex_temp->addEdge(edge);
                    }
                }
                this->graph_time->addVex(vex_temp);
            }else {
                vex_temp->addEvent(event);
            }

        }
    }

    return this->graph_time;
}
