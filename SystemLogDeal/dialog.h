#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "data.h"
#include "myclass.h"
#include "mygraph.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    /*
    ** 显示event的所有信息在textBrowser上
    */
    showData(MyEvent *event);
    ~Dialog();

private:
    Ui::Dialog *ui;
    MyEvent *event;
};

#endif // DIALOG_H
