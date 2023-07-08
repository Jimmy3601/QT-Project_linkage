
#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <cmath>
#include <iostream>
#include <list>

//base class of all movable objects, including plyaers, bullets and player-created obstacles
using namespace std;

const int wallThickness = 10;
const int wallLength = 150;
const double PIX_MULTIPLIER = 1.0;

struct Rect{
    int x, y; //top-left corner
    bool is_horizontal;
    Rect(int _x, int _y, bool _h): x(_x), y(_y), is_horizontal(_h){};
};


bool judge_wall_collision(int x, int y, int r, Rect** rect);

class Player;
class Bullet;

class Object: public QGraphicsPixmapItem
{

public:
    //~Object();
    double radius;  //for circle
    double x_size, y_size; // for rectangle
    double vx, vy, v;
    double v_max;
    int angle, angular_velocity;
    int id;
    bool is_circle; //1: circular; 0: rectangular
    bool is_deleted;
    Object(int x, int y, double r, double vmx, int id_, const QPixmap *pixmap_, QGraphicsScene *scene_, double v_ = 0, int angle_=0);
    Object(int x, int y, double sx, double sy, int vmx, int id_, const QPixmap *pixmap_, QGraphicsScene *scene_, double v_ = 0, int angle_=0);
    QGraphicsScene *scene;

    void change_velocity(double d);
    void change_angle(int d);

    virtual void object_update(QList<Object*> & exo, Rect** rect);
    virtual QPoint get_centre();
    virtual void player_collide(Player *target);

    bool operator==(const Object &other);
    bool operator!=(const Object &other);
    operator int();

    friend class Game;
private:

};

#endif // OBJECT_H
