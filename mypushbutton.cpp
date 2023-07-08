#include "mypushbutton.h".h"
#include<QDebug>
#include<QString>
#include<QPropertyAnimation>
#include<QBitmap>
#include<QPainter>

MyPushButton::MyPushButton(QWidget* parent,bool mask,QString normalImg,QString pressedImg):normalImgPath(normalImg),pressedImgPath(pressedImg),QPushButton(parent)
{
    setCursor(Qt::PointingHandCursor); // 设置鼠标形状
    QPixmap pix;
    bool ret = pix.load(normalImgPath); // 加载图片
    pix = pix.scaled(pix.size() * 1.1, Qt::KeepAspectRatio, Qt::SmoothTransformation); // 改变图片大小并使用平滑缩放算法
    if(!ret)
    {
        qDebug() << "图片加载失败";
        return;
    }
    setFixedSize(pix.width(), pix.height()); // 调整按钮大小
    if(mask)
        setMask(pix.mask()); // 设置遮罩
    setStyleSheet("QPushButton{border:0px;}"); // 调整无边框

    // 创建临时QPixmap对象进行绘制以抗锯齿
    QPixmap tempPix(pix.size());
    tempPix.fill(Qt::transparent);
    QPainter painter(&tempPix);
    painter.setRenderHint(QPainter::Antialiasing); // 设置抗锯齿
    painter.drawPixmap(0, 0, pix);
    painter.end();

    setIcon(tempPix); // 设置按钮图像
    setIconSize(QSize(pix.width(), pix.height())); // 设置图像大小

}



void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    move(x()+1,y()+1);
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{

    move(x()-1,y()-1);
    return QPushButton::mouseReleaseEvent(e);
}
void MyPushButton::enterEvent(QEnterEvent *event)
{

    if(pressedImgPath!="")
    {

        QPixmap pix;
        pix.load(pressedImgPath); // 加载图片

        // 平滑缩放图像
        pix = pix.scaled(pix.size() * 1.1, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // 创建临时QPixmap对象进行绘制以抗锯齿
        QPixmap tempPix(pix.size());
        tempPix.fill(Qt::transparent);
        QPainter painter(&tempPix);
        painter.setRenderHint(QPainter::Antialiasing); // 设置抗锯齿
        painter.drawPixmap(0, 0, pix);
        painter.end();

        setIcon(tempPix); // 设置按钮图像

    }
    return QPushButton::enterEvent(event);
}

void MyPushButton::leaveEvent(QEvent *event)
{
    if(pressedImgPath!="")
    {
        QPixmap pix;
        pix.load(normalImgPath); // 加载图片

        // 平滑缩放图像
        pix = pix.scaled(pix.size() * 1.1, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // 创建临时QPixmap对象进行绘制以抗锯齿
        QPixmap tempPix(pix.size());
        tempPix.fill(Qt::transparent);
        QPainter painter(&tempPix);
        painter.setRenderHint(QPainter::Antialiasing); // 设置抗锯齿
        painter.drawPixmap(0, 0, pix);
        painter.end();

        setIcon(tempPix); // 设置按钮图像

    }
    return QPushButton::leaveEvent(event);
}
