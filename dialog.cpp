#include "dialog.h"
#include "./ui_dialog.h"
#include <QPushButton>
#include "config.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    cnt(0){
    ui->setupUi(this);

    setWindowIcon(QIcon(":/menu/res/qygh.png"));
    setFixedSize(MAX_SCREEN_WIDTH,MAX_SCREEN_HEIGHT);
    setWindowTitle("游戏介绍");


}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    bg[cnt]=bg[cnt].scaled(size(),Qt::KeepAspectRatioByExpanding);
    painter.drawImage(0,0,bg[cnt]);
}

void Dialog::on_NextButton1_clicked()
{
    //bg=QImage(":/res/intr2.png");
    cnt++;
    if(cnt==2){
        auto pbutton = this->findChild<QPushButton*>("NextButton1");
        //pbutton->setVisible(false);
        pbutton->setText("退出");
    }
    if(cnt==3) delete(this);
    else update();

}

