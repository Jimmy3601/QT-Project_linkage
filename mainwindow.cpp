
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "config.h"
#include "game.h"

QString IMG_SRC = ":/menu/res/qygh.png";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/menu/res/qygh.png"));
    setFixedSize(MAX_SCREEN_WIDTH,MAX_SCREEN_HEIGHT);
    setWindowTitle("谁是人上人？");

    QGraphicsScene *st = new QGraphicsScene(this);
    Game *game_scene = new Game;
    st->setSceneRect(0, 0, 1000, 800);
    st->setItemIndexMethod(QGraphicsScene::NoIndex);
    QGraphicsView *v = new QGraphicsView(game_scene, this);
    v->setParent(this);
    //QPixmap test =QPixmap(":/menu/res/qygh.png");

    v->setGeometry(0,0 , 1000 , 800);
    v->setFixedSize(1000,800);
    v->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff) ;
    v->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff ) ;
    //test = test.scaled(100,100);
    //v->setBackgroundBrush(test);
    //QGraphicsPixmapItem *qg = new QGraphicsPixmapItem(test);
    //qg->setPixmap(test);

    //qg->setFlag(QGraphicsItem::ItemIsMovable, true);
    //st->addItem(qg);
    //qg->update();
    //qg->moveBy(100,100);
    //qg->setRotation(180);
    v->show();
    game_scene->game_start();

    //设置退出弹框+按钮
    //connect(ui->menu,&Mymenu::readyforquit,[=](){
    /*ShapedWindow* quitwindow=new ShapedWindow(this,":/menu/res/QuitWindow.png");
        quitwindow->move((this->width()-quitwindow->width())*0.5,(this->height()-quitwindow->height())*0.5);

        MyPushButton* quit=new MyPushButton(quitw  indow,true,":/menu/res/QuitButton.png");
        connect(quit,&MyPushButton::clicked,[=](){
            this->close();
        });
        quit->move(40,210);


        MyPushButton* cancel=new MyPushButton(quitwindow,true,":/menu/res/CancelButton.png");
        connect(cancel,&MyPushButton::clicked,[=](){
            delete quitwindow;
        });
        cancel->move(270,210);
        quitwindow->show();*/
    //});
}

MainWindow::~MainWindow()
{
    delete ui;
}

