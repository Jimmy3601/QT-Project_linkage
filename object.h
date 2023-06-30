
#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <cmath>
#include <iostream>
#include <list>

//base class of all movable objects, including plyaers, bullets and player-created obstacles
using namespace std;



class Object: public QGraphicsPixmapItem
{

public:
    //~Object();
    double radius; //for collide use
    double vx, vy, v;
    double v_max;
    int angle;
    Object(int x, int y, int r, int vmx, const QPixmap *pixmap_, QGraphicsScene *scene_, double v_ = 0, int angle_=0);
    QGraphicsScene *scene;

    void change_velocity(double d);
    void change_angle(int d);

    virtual void object_update();
    virtual QPoint get_centre();

    friend class Game;
private:

};

#endif // OBJECT_H
