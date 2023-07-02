
#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"

class Bullet;

class Player: public Object
{

public:
    Player(int x, int y, int r, int id_, const QPixmap *pixmap_, QGraphicsScene *scene_, int initial_angle);
    //~Player();
    int health, health_max;

    virtual void shoot();
    virtual void object_update(const QVector<Object*> & exo);
    virtual void on_hurt(int damage);
};

#endif // PLAYER_H
