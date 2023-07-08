#ifndef CHOOSE_H
#define CHOOSE_H

#include <QDialog>
#include <QPainter>
#include "object.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class Choose;
}
QT_END_NAMESPACE

class Choose : public QDialog
{
    Q_OBJECT

public:
    explicit Choose(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void showbutton();
    ~Choose();
    bool chosen1,chosen2;
    int label[2];
    QGraphicsView *v;
    void game_end(int _flag);


private:
    Ui::Choose *ui;
    //PreviousWindow* previousWindow; // 上一个窗口的指针
};

#endif // CHOOSE_H


