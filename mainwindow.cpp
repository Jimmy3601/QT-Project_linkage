#include "mypushbutton.h"
#include "mainwindow.h"
//#include <windows.h>
//#include <mmsystem.h>
#include "./ui_mainwindow.h"
#include "config.h"
#include <QDir>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),cntBGM(0)
{
    ui->setupUi(this);
    /*QString path = QDir(":").absolutePath();
    std::cout << path.toStdString() << std::endl;
    wchar_t a[256];
    ("open" + path).toWCharArray(a);
    wchar_t b[256];
    ("play" + path).toWCharArray(b);*/

    setWindowIcon(QIcon(":/menu/res/gh.png"));
    setFixedSize(MAX_SCREEN_WIDTH,MAX_SCREEN_HEIGHT);
    setWindowTitle("谁是人上人？");

    MyPushButton* quit_button = new MyPushButton(this,true,":/res/exit.png",":/res/exit1.png");
    quit_button->move(100,490);
    connect(quit_button,&MyPushButton::clicked,this,[=](){
        qDebug()<<"点了退出！";
        delete this;
    });

    MyPushButton* start_button = new MyPushButton(this,true,":/res/startgame.png",":/res/startgame1.png");
    start_button->move(150,270);
    connect(start_button,&MyPushButton::clicked,this,[=](){
        qDebug()<<"点了开始！";
        this->close();
        auto b = new Choose(this);
        b->show();
    });

    MyPushButton* intro_button = new MyPushButton(this,true,":/res/introduction.png",":/res/introduct1.png");
    intro_button->move(200,380);
    connect(intro_button,&MyPushButton::clicked,this,[=](){
        auto a = new Dialog(this);

        a->show();
    });

    /*MyPushButton* BGM = new MyPushButton(this,true,":/res/BGM.png",":/res/BGM1.png");
    BGM->move(900,700);
    connect(BGM,&MyPushButton::clicked,this,[=](){
        cntBGM++;
        if(cntBGM%2==1){
            mciSendString(L"open C:\\Users\\lml\\Documents\\GitHub\\QT-Project\\res\\bkmusic.mp3",0,0,0);
            mciSendString(L"play C:\\Users\\lml\\Documents\\GitHub\\QT-Project\\res\\bkmusic.mp3",0,0,0);
        }
        else {
            mciSendString(L"close C:\\Users\\lml\\Documents\\GitHub\\QT-Project\\res\\bkmusic.mp3",0,0,0);
        }//绝对路径，间接不行，需要修改
    });*/
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); // 设置抗锯齿和平滑绘图

    QImage bg(":/menu/res/bk.png");
    bg = bg.scaled(size(), Qt::KeepAspectRatioByExpanding);
    painter.drawImage(0, 0, bg);

}

MainWindow::~MainWindow()
{
    delete ui;
}
