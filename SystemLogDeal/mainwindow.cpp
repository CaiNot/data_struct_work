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
//    my->createGraphByTime();
    this->graph=my->graph;
    showGraphData(my->graph);

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
    if(ui->tableWidget->horizontalHeaderItem(0)->text()=="Provider"){
        position=ui->tableWidget->currentRow();
        if(position==-1)
            position=0;
        showVexData(this->graph->vexList->at(position));
    }else if(ui->tableWidget->horizontalHeaderItem(0)->text()=="EventRecordID"){
        position=ui->tableWidget->currentRow();
        if(position==-1)
            position=0;
        showEventData(this->vex->eventList->at(position));
    }
}

void MainWindow::on_delBtn_clicked()
{

}

void MainWindow::on_insertBtn_clicked()
{

}

void MainWindow::on_backBtn_clicked()
{
    if(ui->tableWidget->horizontalHeaderItem(0)->text()=="EventRecordID"){
        showGraphData(this->graph);
    }
}
