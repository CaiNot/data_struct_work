#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
//    ui->treeWidget->setEditTriggers(QAbstractItemView::DoubleClicked);

}

Dialog::showData(MyEvent *event)
{
//    QTreeWidgetItem *item_event=new QTreeWidgetItem(ui->treeWidget,QStringList(event->event_data->id)),
//            *item_system=new QTreeWidgetItem(ui->treeWidget,QStringList(event->system_data->id)),
//            *item_render=new QTreeWidgetItem(ui->treeWidget,QStringList(event->render_data->id));

    QList<QString> *list_name=NULL,*list_detail=NULL;


    int length=0;
//    QTreeWidgetItem *item_father=NULL;
    for(int i=0;i<3;i++){
        if(i==0)
        {
//            item_father=item_system;
            list_name=event->system_data->names;
            list_detail=event->system_data->details;
        }
        else if(i==1){
//            item_father=item_event;
            list_name=event->event_data->names;
            list_detail=event->event_data->details;
        }
        else
        {
//            item_father=item_render;
            list_name=event->render_data->names;
            list_detail=event->render_data->details;
        }
        length=list_name->length();
        for (int i=0;i<length;i++){
//            QTreeWidgetItem *item=new QTreeWidgetItem(item_father,QStringList(list_name->at(i)));
//            QTreeWidgetItem *item_son=new QTreeWidgetItem(item,QStringList(list_detail->at(i)));
            this->ui->textBrowser->insertPlainText(list_name->at(i)+"\t");
            this->ui->textBrowser->insertPlainText(list_detail->at(i)+"\n");
        }
        this->ui->textBrowser->insertPlainText("\n");
    }
}

Dialog::~Dialog()
{
    delete ui;
}
