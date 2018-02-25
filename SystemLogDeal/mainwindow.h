#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "data.h"
#include "myclass.h"
#include "mygraph.h"
#include "xmlgetter.h"

#include <QTableWidget>
#include "dialog.h"
#include <QMessageBox>
#include <QFileDialog>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    int showGraphData(MyGraph *graph);
    int showGraphDataTime(MyGraph *graph_time);
    int showVexData(MyVex *vex);
    int showEventData(MyEvent *event);

    ~MainWindow();

private slots:

    void on_openBtn_clicked();

    void on_delBtn_clicked();

    void on_insertBtn_clicked();

    void on_backBtn_clicked();

    void on_actionSearch_triggered();

    void on_actionsave_triggered();

private:
    Ui::MainWindow *ui;

    QStringList header;
    QString level_events,last_src;
    MyGraph *graph,*graph_time;
    MyVex *vex,*vex_temp;
    MyEdge *edge,*edge_temp;
    MyEvent *event,*event_temp;

    QList<MyVex *> *vexs_list;
    QList<MyEvent *> *events_list;


};

#endif // MAINWINDOW_H
