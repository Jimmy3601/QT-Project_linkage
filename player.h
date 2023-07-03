
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
    int shoot_interval; // in ms
    bool is_hurt;
    int buff, buff_duration; //in ms
    /*buff list(id)
     * 0: none
     * 1: gain 100%/400% extra movement speed
     * 2: gain 100%/400% extra bullet speed
     * 3: gain 100%/400% extra rotation speed
     * 4: bullet deal 100%/300% extra damage
     * 5: shoot interval beecome 0.5/0.2 s
     * instant effect: heal 1/5 health
     * */

    virtual void shoot();
    virtual void object_update(QList<Object*> & exo);
    virtual void on_hurt(int damage);
    virtual void use_skill();
};

class Eecs{

};

class Guanghua {

};

class Yuanpei{

};

class Xinya{

};

#endif // PLAYER_H
