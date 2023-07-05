
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
    int bullet_vmax, bullet_damage;
    bool is_hurt, is_buff_rare;
    int buff_id, buff_duration, skill_duration; //in ms


    virtual void shoot();
    virtual void object_update(QList<Object*> & exo);
    virtual void on_hurt(int damage);
    virtual void use_skill();

    void grant_buff(int _id, bool is_rare);
    void remove_buff();
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
