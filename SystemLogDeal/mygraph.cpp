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
