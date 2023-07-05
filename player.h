
#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"

class Bullet;

class Player: public Object
{
public:
    Player(int x, int y, int r, int id_, const QPixmap *pixmap_, QGraphicsScene *scene_, int initial_angle, int _f);
    //~Player();
    int health, health_max;
    int shoot_interval; // in ms
    int bullet_vmax, bullet_damage, bullet_radius;
    bool is_hurt, is_buff_rare, is_using_skill;
    int buff_id, buff_duration, skill_duration; //skill_duration for both during-skill and cooldown use
    int faculty;


    virtual void shoot();
    virtual void object_update(QList<Object*> & exo);
    virtual void on_hurt(int damage);
    virtual void use_skill();
    virtual void skill_expired();

    void grant_buff(int _id, bool is_rare);
    void remove_buff();
};

class Eecs: public Player{
public:
    Eecs(int x, int y, int r, int id_,const QPixmap *pixmap, QGraphicsScene *scene_, int initial_angle);
    virtual void use_skill();
    virtual void on_hurt(int damage);
    virtual void skill_expired();
};

class Guanghua: public Player {
public:
    Guanghua(int x, int y, int r, int id_,const QPixmap *pixmap, QGraphicsScene *scene_, int initial_angle);
    virtual void use_skill();
    virtual void skill_expired();
};

class Yuanpei: public Player{
public:
    Yuanpei(int x, int y, int r, int id_,const QPixmap *pixmap, QGraphicsScene *scene_, int initial_angle);
};

class Xinya: public Player{
public:
   Xinya(int x, int y, int r, int id_,const QPixmap *pixmap, QGraphicsScene *scene_, int initial_angle);
   virtual void use_skill();
   virtual void skill_expired();
};

#endif // PLAYER_H
