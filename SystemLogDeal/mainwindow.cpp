#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString PATH="D:\\SystemXML_1.xml";
    XMLGetter *getter=new XMLGetter();
    getter->getXML(PATH);

    MyClass *my=new MyClass();
    my->graph=getter->graph;
    my->createGraphByTime();
    this->graph=my->graph;
    this->graph_time=my->graph_time;
        showGraphData(my->graph);
//    this->graph=my->graph_time;
//    showGraphDataTime(this->graph_time);

}

int MainWindow::showGraphData(MyGraph *graph)
{
    if(graph==NULL)
        return 1;
    ui->tableWidget->clear();
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);

    this->header.clear();
    header<<"Provider"<<"Nums"<<"Levels";
    this->ui->tableWidget->setRowCount(graph->vexList->length());
    ui->tableWidget->setHorizontalHeaderLabels(header);

    int rowPosition=0,length_vexs=0;

    this->vexs_list=graph->vexList;
    length_vexs=this->vexs_list->length();
    for (int i=0;i<length_vexs; i++) {
        MyVex *v=this->vexs_list->at(i);
        ui->tableWidget->setItem(rowPosition,0,new QTableWidgetItem(v->provider));
        ui->tableWidget->setItem(rowPosition,1,new QTableWidgetItem(QString::number(v->eventList->length())));
        ui->tableWidget->setItem(rowPosition,2,new QTableWidgetItem(v->getLevels()));
        rowPosition++;
    }

    return 0;

}

int MainWindow::showGraphDataTime(MyGraph *graph_time)
{
    if(graph_time==NULL)
        return 1;
    ui->tableWidget->clear();
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);

    this->header.clear();
    header<<"Time"<<"Nums"<<"Levels";
    this->ui->tableWidget->setRowCount(graph_time->vexList->length());
    ui->tableWidget->setHorizontalHeaderLabels(header);

    int rowPosition=0,length_vexs=0;

    this->vexs_list=graph_time->vexList;
    length_vexs=this->vexs_list->length();
    for (int i=0;i<length_vexs; i++) {
        MyVex *v=this->vexs_list->at(i);
        ui->tableWidget->setItem(rowPosition,0,new QTableWidgetItem(v->time));
        ui->tableWidget->setItem(rowPosition,1,new QTableWidgetItem(QString::number(v->eventList->length())));
        ui->tableWidget->setItem(rowPosition,2,new QTableWidgetItem(v->getLevels()));
        rowPosition++;
    }

    return 0;
}

int MainWindow::showVexData(MyVex *vex)
{
    if(vex==NULL){
        return 1;
    }
    this->vex=vex;
    ui->tableWidget->clear();
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);

    this->header.clear();
    header<<"EventRecordID"<<"Time"<<"Level";
    this->ui->tableWidget->setRowCount(vex->eventList->length());
    ui->tableWidget->setHorizontalHeaderLabels(header);

    int rowPosition=0,length_events=0;
    this->events_list=vex->eventList;
    length_events=this->events_list->length();
    for(int i=0;i<length_events;i++){
        this->event_temp=this->events_list->at(i);
        ui->tableWidget->setItem(rowPosition,0,new QTableWidgetItem(this->event_temp->system_data->getDetailByNameString("EventRecordID")));
        ui->tableWidget->setItem(rowPosition,1,new QTableWidgetItem(this->event_temp->system_data->getDetailByNameString("TimeCreated")));
        ui->tableWidget->setItem(rowPosition,2,new QTableWidgetItem(this->event_temp->render_data->getDetailByNameString("Level")));
        rowPosition++;
    }

    return 0;
}

int MainWindow::showEventData(MyEvent *event)
{
    if(event==NULL){
        return 1;
    }
    Dialog *dialog=new Dialog();
    dialog->showData(event);
    dialog->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_openBtn_clicked()
{
    int position=0;
    QString head_text=ui->tableWidget->horizontalHeaderItem(0)->text();
    if(head_text=="Provider"||head_text=="Time"){
        position=ui->tableWidget->currentRow();
        if(position==-1)
            position=0;

        last_src=head_text;
        showVexData(this->graph->vexList->at(position));
    }else if(head_text=="EventRecordID"){
        position=ui->tableWidget->currentRow();
        if(position==-1)
            position=0;
        showEventData(this->vex->eventList->at(position));
    }
}

void MainWindow::on_delBtn_clicked()
{
    int position=0;
    position=ui->tableWidget->currentRow();
    if(position==-1){
        QMessageBox::information(this,"Infomation","You haven't choosen anything!");
        return;
    }

        QMessageBox::StandardButton resultBtn=QMessageBox::question(this,"Delete","Are you sure to delete this ?");
        if(resultBtn==QMessageBox::Yes){
            QString head_str=this->ui->tableWidget->horizontalHeaderItem(0)->text();
            if(head_str=="Provider"){
                this->graph->vexList->removeAt(position);
                qDebug()<<"aaa";
            }else if(head_str=="Time"){
                this->graph->vexList->at(position);
            }

        }else if(resultBtn==QMessageBox::No){

        }

}

void MainWindow::on_insertBtn_clicked()
{

}

void MainWindow::on_backBtn_clicked()
{
    if(ui->tableWidget->horizontalHeaderItem(0)->text()=="EventRecordID"){
        if(last_src=="Provider")
        {
            showGraphData(this->graph);
        }
        else
        {
            showGraphDataTime(this->graph);
        }
    }
}

void MainWindow::on_actionSearch_triggered()
{

}

void MainWindow::on_actionsave_triggered()
{
    QString path=QFileDialog::getSaveFileName(this,"Save",".","*.xml");
    if(path.length()==0){
        QMessageBox::information(this,"NULL","You didn't choose anything!");
    }else {
        QFile file(path);
        //        if(!file.open(QIODevice::ReadWrite)){

        //        }
        XMLGetter *get=new XMLGetter();
        get->writeXML(path,this->graph);

        QMessageBox::information(this,"Save","Data has saved in "+path);
    }

}
