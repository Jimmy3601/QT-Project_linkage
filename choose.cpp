#include "choose.h"
#include "mainwindow.h"
#include "shapedwindow.h"
#include "./ui_choose.h"
#include <QPushButton>
#include "config.h"
#include "mypushbutton.h"
#include <QDebug>
#include <QString>
#include <QPropertyAnimation>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBitmap>
#include "game.h"

Choose::Choose(QWidget *parent) :
    QDialog(parent),ui(new Ui::Choose)
{
    v = nullptr;
    ui->setupUi(this);
    setWindowIcon(QIcon(":/menu/res/qygh.png"));
    setFixedSize(MAX_SCREEN_WIDTH,MAX_SCREEN_HEIGHT);
    setWindowTitle("选择角色");
    chosen1=false ,chosen2=false;
    label[0] = 0, label[1] = 0;

    MyPushButton* xk1=new MyPushButton(this,true,":/menu/res/xk.png",":/res/xkback.png");
    xk1->move(115,250);
    connect(xk1,&MyPushButton::clicked,this,[=](){
        MyPushButton* xk11 = new MyPushButton(this,true,":/menu/res/xk.png");
        xk11->move(335,150);
        xk11->show();
        chosen1 = true;
        if(chosen1&&chosen2) showbutton();
        label[0] = 0;
        qDebug()<<"点了！";
    });

    MyPushButton* xk2=new MyPushButton(this,true,":/menu/res/xk.png",":/res/xkback.png");
    xk2->move(775,250);
    connect(xk2,&MyPushButton::clicked,this,[=](){
        MyPushButton* xk22 = new MyPushButton(this,true,":/menu/res/xk.png");
        xk22->move(565,150);
        xk22->show();
        chosen2 = true;
        if(chosen1&&chosen2) showbutton();
        label[1] = 0;
        qDebug()<<"点了！";
    });

    MyPushButton* gh1=new MyPushButton(this,true,":/menu/res/qygh2.png",":/res/qyghback.png");
    gh1->move(115,390);
    connect(gh1,&MyPushButton::clicked,this,[=](){
        MyPushButton* gh11 = new MyPushButton(this,true,":/menu/res/qygh2.png");
        gh11->move(335,150);
        gh11->show();
        chosen1 = true;
        if(chosen1&&chosen2) showbutton();
        label[0] = 1;
        qDebug()<<"点了！";
    });

    MyPushButton* gh2=new MyPushButton(this,true,":/menu/res/qygh2.png",":/res/qyghback.png");
    gh2->move(775,390);
    connect(gh2,&MyPushButton::clicked,this,[=](){
        MyPushButton* gh22 = new MyPushButton(this,true,":/menu/res/qygh2.png");
        gh22->move(565,150);
        gh22->show();
        chosen2 = true;
        if(chosen1&&chosen2) showbutton();
        label[1] = 1;
        //qDebug()<<"点了！";
    });

    MyPushButton* yp1=new MyPushButton(this,true,":/menu/res/yp.png",":/res/ypback.png");
    yp1->move(115,530);
    connect(yp1,&MyPushButton::clicked,this,[=](){
        MyPushButton* yp11 = new MyPushButton(this,true,":/menu/res/yp.png");
        yp11->move(335,150);
        yp11->show();
        chosen1 = true;
        if(chosen1&&chosen2) showbutton();
        label[0] = 2;
        //qDebug()<<"点了！";
    });

    MyPushButton* yp2=new MyPushButton(this,true,":/menu/res/yp.png",":/res/ypback.png");
    yp2->move(775,530);
    connect(yp2,&MyPushButton::clicked,this,[=](){
        MyPushButton* yp22 = new MyPushButton(this,true,":/menu/res/yp.png");
        yp22->move(565,150);
        yp22->show();
        chosen2 = true;
        if(chosen1&&chosen2) showbutton();
        label[1] = 2;
        qDebug()<<"点了！";
    });

    MyPushButton* xy1=new MyPushButton(this,true,":/menu/res/xy.png",":/res/xyback.png");
    xy1->move(115,670);
    connect(xy1,&MyPushButton::clicked,this,[=](){
        MyPushButton* xy11 = new MyPushButton(this,true,":/menu/res/xy.png");
        xy11->move(335,150);
        xy11->show();
        chosen1 = true;
        if(chosen1&&chosen2) showbutton();
        label[0] = 3;
        qDebug()<<"点了！";
    });

    MyPushButton* xy2=new MyPushButton(this,true,":/menu/res/xy.png",":/res/xyback.png");
    xy2->move(775,670);
    connect(xy2,&MyPushButton::clicked,this,[=](){
        MyPushButton* xy22 = new MyPushButton(this,true,":/menu/res/xy.png");
        xy22->move(565,150);
        xy22->show();
        chosen2 = true;
        if(chosen1&&chosen2) showbutton();
        label[1] = 3;
        //qDebug()<<"点了！";
    });

}

Choose::~Choose()
{
    delete ui;
}

void Choose::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); // 设置抗锯齿和平滑绘图
    QImage bg(":/menu/res/choose.png");
    bg=bg.scaled(size(),Qt::KeepAspectRatioByExpanding);
    painter.drawImage(0,0,bg);
}

void Choose::showbutton()
{
    MyPushButton* startbutton = new MyPushButton(this,true,":/res/start.png",":/res/start1.png");
    startbutton->move(785,45);
    startbutton->show();
    connect(startbutton,&MyPushButton::clicked,this,[=](){
        qDebug()<<"label1="<<label[0]<<" label2="<<label[1];
        setWindowTitle("决一胜负！");
        QGraphicsScene *st = new QGraphicsScene(this);
        Game *game_scene = new Game(this, label[0],label[1]);
        st->setSceneRect(0, 0, 1000, 800);
        st->setItemIndexMethod(QGraphicsScene::NoIndex);
        v = new QGraphicsView(game_scene, this);
        v->setParent(this);

        v->setGeometry(0,0 , 1000 , 800);
        v->setFixedSize(1000,800);
        v->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        v->setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
        //test = test.scaled(100,100);
        v->setRenderHints(QPainter::Antialiasing);
        v->show();
        game_scene->game_start();
        //v->hide();
        //this->hide();



    });
    //qDebug()<<"show button";
}

void Choose::game_end(int _flag) {
    QString quitwindow_path , quitIcon_path;
    if(_flag==0) quitwindow_path = ":/res/over1.png";
    else quitwindow_path = ":/res/over2.png";
    switch (label[_flag]) {
    case 0:
        quitIcon_path = ":/menu/res/xk.png";
        break;
    case 1:
        quitIcon_path = ":/menu/res/qygh2.png";
        break;
    case 2:
        quitIcon_path = ":/menu/res/yp.png";
        break;
    case 3:
        quitIcon_path = ":/menu/res/xy.png";
        break;
    }

    ShapedWindow* quitwindow=new ShapedWindow(this,quitwindow_path);
    quitwindow->move(250,195);


    ShapedWindow* quitIcon=new ShapedWindow(quitwindow,quitIcon_path);
    quitIcon ->move(60,220);
    quitIcon->show();

    MyPushButton* backcd = new MyPushButton(quitwindow,true,":/menu/res/backcd.png",":/res/backcd1.png");
    backcd->move(50,330);
    connect(backcd,&MyPushButton::clicked,this,[=](){
        v->hide();
        this->close();
        auto a = new MainWindow(this);
        a->show();

        //qDebug()<<"点了backcd！";
    });

    MyPushButton* saygoodbye = new MyPushButton(quitwindow,true,":/menu/res/saygoodbye.png",":/res/saygoodbye1.png");
    saygoodbye->move(305,330);
    connect(saygoodbye,&MyPushButton::clicked,this,[=](){
        delete this;
        //qDebug()<<"点了saygoodbye！";
    });

    quitwindow->show();
}
