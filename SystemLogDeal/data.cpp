#include "data.h"

MyData::MyData()
{
    this->names=new QList<QString>();
    this->details=new QList<QString>();
}

MyData::MyData(QString id)
{
    this->id=id;
    this->names=new QList<QString>();
    this->details=new QList<QString>();
}

MyData::setID(QString id)
{
    this->id=id;
}

MyData::addName(QString name)
{
    this->names->append(name);
}

MyData::addDetails(QString detail)
{
    this->details->append(detail);
}

QString MyData::getDetailByNameString(QString name)
{
    int position=getDetailByNameInt(name);
    if(position>-1){
        return this->details->at(position);
    }
    return NULL;

}

int MyData::getDetailByNameInt(QString name)
{
    int length=this->names->length();
    QString name_in_list;
    for(int i=0;i<length;i++){
        name_in_list=names->at(i);
        if(name==name_in_list){
            return i;
        }
    }
    return -1;
}

MyData::~MyData()
{
    this->names->clear();
    free(names);
    this->details->clear();
    free(details);
}

MyEvent::MyEvent()
{
    this->event_data=NULL;
    this->system_data=NULL;
    this->next_event=NULL;
}

MyEvent::setEventData(MyData *event)
{
    this->event_data=event;
}

MyEvent::setSystemData(MyData *system_data)
{
    this->system_data=system_data;
}

MyEvent::setTime(QString time)
{
    this->time=time;
}

QString MyEvent::changeTime()
{
    QString temp;
    this->time=this->time.left(16);
    int length=this->time.length();
    for(int i=0;i<length;i++){
        if(this->time.at(i)>='0'&&this->time.at(i)<='9'){
            temp.append(this->time.at(i));
        }
    }
    this->time=temp;

    return temp;
}

MyEvent::setRecordID(QString id)
{
    this->record_id=id;
}

MyEvent::~MyEvent()
{
    event_data->~MyData();
    system_data->~MyData();
    free(event_data);
    free(system_data);
}
