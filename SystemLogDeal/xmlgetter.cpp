#include "xmlgetter.h"


int XMLGetter :: getXML(QString PATH){
    xmlDoc=new QDomDocument();
    file=new QFile(PATH);
    if(!file->open(QIODevice::ReadOnly)){
        return 1;
    }
    if(!xmlDoc->setContent(file)){
        file->close();
        return 1;
    }
    file->close();

    QDomElement docElem = xmlDoc->documentElement();

    createEvent(&docElem);
}

QDomElement *XMLGetter::readXML(QDomElement *element)
{
    if(!element->isNull()){

        QDomNode n = element->firstChild();
        while(!n.isNull()) {
            QDomElement e = n.toElement(); // 尝试将节点转换为元素

            if(!e.isNull()) {
                if(e.tagName()=="System"){
                    qDebug()<<"1:"<<this->count++;
                    data=new MyData("System");
                }
                if(e.tagName()=="EventData"){
                    qDebug()<<"2:"<<this->count++;
                    data=new MyData("EventData");
                }
                qDebug() << e.tagName();


                QDomNamedNodeMap map= e.attributes();// 获取元素的属性
                for(int i=0;i<map.length();i++){
                    //                    qDebug()<<map.item(i).nodeValue();
                }
                if(e.firstChildElement().isNull()){
                    //                    qDebug()<<e.text()<<endl; // 节点真的是一个元素
                }
                //                if(this->count>100)
                //                    break;
                readXML(&e);

            }
            n = n.nextSibling();

        }

    }
    return NULL;
}

int XMLGetter::createEvent(QDomElement *element)
{
    if(!element->isNull()){

        this->graph=new MyGraph();

        QDomNode n = element->firstChild();
        while(!n.isNull()) {// Event层
            QDomElement e = n.toElement(); // 尝试将节点转换为元素

            if(!e.isNull()) {
                this->event=new MyEvent();

                QDomElement e_1=e.firstChildElement();
                if(!e_1.isNull()){// Event 子层
                    int i=0;
                    do{
                        i++;
                        if(i==1)
                        {
                            this->system_data=new MyData("System");
                            this->data=this->system_data;
                        }
                        else if(i==2)
                        {
                            this->event_data=new MyData("EventData");
                            this->data=this->event_data;
                        }
                        else {
                            this->render_data=new MyData("RenderingInfo");
                            this->data=this->render_data;
                        }

                        QDomElement e_2=e_1.firstChildElement();
                        do{
                            this->data->addName(e_2.tagName());
                            if(i==1&&e_2.tagName()=="Provider"){
                                this->event->setRecordID(e_2.attribute("Name"));
                                this->data->addDetails(e_2.attribute("Name"));
                            }
                            else if(i==1&&e_2.tagName()=="TimeCreated"){
                                this->data->addDetails(e_2.attribute("SystemTime"));
                            }
                            else   {
                                this->details=e_2.text();
                                //                            QDomNamedNodeMap map= e_2.attributes();// 获取元素的属性
                                //                                for(int i=0;i<map.length();i++){
                                //                                    this->details+=map.item(i).nodeValue();
                                //                                }
                                this->data->addDetails(this->details);
                            }
                            e_2=e_2.nextSiblingElement();
                        }while(!e_2.isNull());


                        e_1=e_1.nextSiblingElement();
                    }while(!e_1.isNull());
                }
                // save all kinds of data

                this->event->system_data=this->system_data;
                this->event->event_data=this->event_data;
                this->event->render_data=this->render_data;

                //                this->event->setRecordID(this->event->
                //                                         system_data->getDetailByNameString("Provider"));
                this->event->setTime(this->event->
                                     system_data->getDetailByNameString("TimeCreated"));

                // save to Graph
                // its father in the graph ?
                this->vex=graph->getVex(this->event->record_id);
                if(this->vex==NULL){
                    this->vex=new MyVex();
                    this->vex->addEvent(this->event);
                    this->vex->provider=this->event->record_id;

                    graph->addVex(this->vex);
                }else {
                    this->vex->eventList->append(this->event);
                }
            }
            n = n.nextSibling();
        }
    }
    return 0;
}

int XMLGetter::writeXML(QString PATH,MyGraph *graph)
{
//    PATH="d://what.xml";
    QFile file(PATH);

    file.open(QIODevice::ReadWrite);
    QDomDocument doc;

    QString header_str="version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\"";
    doc.appendChild(doc.createProcessingInstruction("xml",header_str));

    QDomElement root=doc.createElement("Events");

    int vex_length=graph->vexList->length();
    int event_length=0;
    this->vex_list=graph->vexList;
    for (int i=0;i<vex_length;i++){
        this->event_list=this->vex_list->at(i)->eventList;
        event_length=this->event_list->length();
        for(int i=0;i<event_length;i++){
            this->event=this->event_list->at(i);

            this->system_data=this->event->system_data;
            this->event_data=this->event->event_data;
            this->render_data=this->event->render_data;

            doc.appendChild(root);
            QDomElement item_event=doc.createElement("Event");
            QDomElement item_system=doc.createElement("System");
            QDomElement item_event_data=doc.createElement("EventData");
            QDomElement item_render=doc.createElement("RenderingInfo");

            QDomElement item_father;
            for(int x=0;x<3;x++){
                if(x==0){
                    item_father=item_system;
                    this->data=this->system_data;
                }else if(x==1){
                    item_father=item_event_data;
                    this->data=this->event_data;
                }else if(x==2){
                    item_father=item_render;
                    this->data=this->render_data;
                }
                int name_length=this->data->names->length();

                for(int i=0;i<name_length;i++){
                    this->name=this->data->names->at(i);
                    QDomElement item=doc.createElement(this->name);
                    if(x==0&&this->name=="Provider"){
                        item.setAttribute("Name",this->data->details->at(i));
                    }else if(x==0&&this->name=="TimeCreated"){
                        item.setAttribute("SystemTime",this->data->details->at(i));
                    }else
                    {QDomText text=doc.createTextNode(this->data->details->at(i));
                    item.appendChild(text);
                    }
                    item_father.appendChild(item);
                }
                item_event.appendChild(item_father);
            }
            root.appendChild(item_event);

        }
    }

    QTextStream out(&file);
    doc.save(out,4);
    file.close();


}


XMLGetter::~XMLGetter()
{

    free(file);
}
