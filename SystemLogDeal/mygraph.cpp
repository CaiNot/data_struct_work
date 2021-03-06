﻿#include "mygraph.h"


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

QMap<MyVex *,int> *MyGraph::getVexTime(QString time, int arrange)
{
    QMap<MyVex *,int> *vex_map=new QMap<MyVex*,int>;
    QList<MyVex *> *vex_list=new QList<MyVex*>,*vex_list_1=new QList<MyVex *>;
    MyVex *vex=getVexTime(time);

    if(vex==NULL)
        return NULL;

    MyEdge *edge_temp=NULL;

    MyVex *vex_temp=vex;

    vex_list->append(vex_temp);

    for(int i=0;i<arrange;i++){
        int length_vex_list=vex_list->length();
        for(int l=0;l<length_vex_list;l++){

            vex=vex_list->at(l);

            edge_temp=vex->firstEdge;

            while(edge_temp!=NULL){
                //        vex_list.append((MyVex*)edge_temp->vex);
//                if(vex==edge_temp->vex)
//                    continue;
                if(vex_map->contains((MyVex*)edge_temp->vex)){
                    vex_map->insert((MyVex*)edge_temp->vex,vex_map->value((MyVex*)edge_temp->vex)+1);
                }else{
                    vex_map->insert((MyVex*)edge_temp->vex,1);
                    vex_list_1->append((MyVex*)edge_temp->vex);
                }

                edge_temp=edge_temp->adjlink;
            }

        }
        vex_list->clear();
        vex_list=vex_list_1;
    }
    return vex_map;
}

QList<MyEvent *> *MyGraph::getProviderEvent(MyVex *vex,int day)
{
    if(vex==NULL){
        return NULL;
    }
    if(vex->eventList->length()<15)
        return vex->eventList;
    else
    {
        QList<MyEvent*> *event_list=new QList<MyEvent*>;
        MyEvent *event=NULL;
        int length=vex->eventList->length(),timeCompare=0;
        for(int i=0;i<length;i++){
            event=vex->eventList->at(i);
            timeCompare=compareTimeStr(vex->time,event->changeTime());
            if(timeCompare<10000*day){
                event_list->append(event);
            }
            if(event->render_data->getDetailByNameString("Level")!="信息"){
                event_list->append(event);
            }
        }
        return event_list;
    }

    return NULL;
}

QMap<QString ,int> *MyGraph::getSimilarEvent(MyVex *vex)
{
    if(vex==NULL)
        return NULL;
    int length=vex->eventList->length();
    MyEvent *event=NULL,*event_temp=NULL;

    QMap<MyVex *,int> *vexMap=NULL;
    QMap<QString,int> *eventMap_provider=new QMap<QString,int>();

//    QList<MyEvent*> event_list=new QList<MyEvent*>;
    QList<MyVex *> vex_list;

    MyVex *vex_temp=NULL;
    for(int i=0;i<length;i++){
        event=vex->eventList->at(i);
        vexMap=getVexTime(event->changeTime(),2);
        vex_list=vexMap->keys();
        int vex_list_length=vex_list.length();

        for(int l=0;l<vex_list_length;l++){
            vex_temp=vex_list.at(l);
            int event_list_length=vex_temp->eventList->length();

            for(int x=0;x<event_list_length;x++){
                event_temp=vex_temp->eventList->at(x);

                if(eventMap_provider->contains(event_temp->record_id)){
                    eventMap_provider->insert(event_temp->record_id,eventMap_provider->value(event_temp->record_id)+1);
                }else{
                    eventMap_provider->insert(event_temp->record_id,1);
                }

            }
        }
    }
    return eventMap_provider;
}

int MyGraph::deleteVex(MyVex *vex)
{
    int length=this->vexList->length();
    MyVex *vex_temp=NULL;
    for(int i=0;i<length;i++){
        vex_temp=this->vexList->at(i);
        vex_temp->deleteEdge(vex);
    }
    return 0;
}

int MyGraph::compareTime(MyVex *vex_1, MyVex *vex_2)
{
    QString time_1=vex_1->time.right(9);
    QString time_2=vex_2->time.right(9);
    int vex_time_1=time_1.toInt();
    int vex_time_2=time_2.toInt();


    //    int num=vex_1->time-vex_2->time;
    return vex_time_1-vex_time_2;
}

int MyGraph::compareTimeStr(QString time_1, QString time_2)
{
    time_1=time_1.right(9);
    time_2=time_2.right(9);
    int vex_time_1=time_1.toInt();
    int vex_time_2=time_2.toInt();


    //    int num=vex_1->time-vex_2->time;
    return vex_time_1-vex_time_2;
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

int MyVex::deleteEdge(MyVex *vex)
{
    MyEdge *edge_temp=this->firstEdge,*edge=this->firstEdge;
    if(edge==NULL){
        return 0;
    }
    if(vex==edge->vex){
        this->firstEdge=edge->adjlink;
        free(edge);
        return 0;
    }
    while (edge_temp!=NULL) {
        edge=edge_temp->adjlink;
        if(edge&&edge->vex==vex){
            edge_temp->adjlink=edge->adjlink;
            free(edge);
            return 0;
        }
        edge_temp=edge;
    }

    return 1;
}

QString MyVex::getLevels()
{
    QString levels;
    QList<QString> levels_list;
    QMap<QString,int> levels_map;

    int length_events=0;
    length_events=this->eventList->length();
    MyEvent *e=NULL;
    for(int i =0;i<length_events;i++){
        e=this->eventList->at(i);
        //        if(i==0){
        //            levels=e->render_data->getDetailByNameString("Level");
        //        }else
        //            levels+=","+e->render_data->getDetailByNameString("Level");

        levels=e->render_data->getDetailByNameString("Level");
        if(levels_map.contains(levels)){
            levels_map.insert(levels,levels_map.value(levels)+1);
        }else{
            levels_map.insert(levels,1);
        }
    }
    levels_list=levels_map.keys();
    int length=levels_list.length();
    levels="";
    for(int i=0;i<length;i++){
        levels+=levels_list.at(i)+" "+QString::number(levels_map.value(levels_list.at(i)))+"\t";
    }

    return levels;
}
