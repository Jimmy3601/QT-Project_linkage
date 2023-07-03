
#ifndef BULLET_H
#define BULLET_H

#include "player.h"


class Bullet: public Object
{
    int damage;
public:
    Bullet(int x, int y, double r, int id_, const QPixmap *pixmap_, QGraphicsScene *scene_, double v_, int a_, int d, Player *p);
    ~Bullet();
    Player *parent;


    virtual void object_update(QList<Object*> & exo);
    virtual void player_collide(Player *target);
};

#endif // BULLET_H
