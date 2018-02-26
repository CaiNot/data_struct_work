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

    /*
    ** 显示graph的信息，按照主客体图显示
    */
    int showGraphData(MyGraph *graph);

    /*
    ** 显示graph的信息，按照时间关系图显示
    */
    int showGraphDataTime(MyGraph *graph_time);

    /*
    ** 显示结点的信息，无论是那种图
    ** 结点显示的信息类型都一样
    */
    int showVexData(MyVex *vex);

    /*
    ** 显示event的信息
    */
    int showEventData(MyEvent *event);

    ~MainWindow();

private slots:

    void on_openBtn_clicked();

    void on_delBtn_clicked();

    void on_insertBtn_clicked();

    void on_backBtn_clicked();

    void on_actionSearch_triggered();

    void on_actionsave_triggered();

    void on_actionfuture_triggered();

    void on_actionbefore_triggered();

    void on_action_triggered();

    void on_actionopen_triggered();

    void on_action_show_graph_triggered();

    void on_action_show_time_triggered();

private:
    Ui::MainWindow *ui;

    QStringList header;
    QString level_events,last_src;
    QString open_path,save_path;

    MyGraph *graph,*graph_time,*graph_from;

    MyVex *vex,*vex_temp;

    MyEdge *edge,*edge_temp;

    MyEvent *event,*event_temp;

    QList<MyVex *> *vexs_list;
    QList<MyEvent *> *events_list;


};

#endif // MAINWINDOW_H
