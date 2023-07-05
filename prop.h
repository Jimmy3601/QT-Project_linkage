
#ifndef PROP_H
#define PROP_H


#include "player.h"

class Prop: public Object
{
public:
    bool is_rare;
    Prop(int x, int y, double r, int id_, const QPixmap *pixmap_, QGraphicsScene *scene_, bool rare);

    virtual void player_collide(Player *target);
};

#endif // PROP_H
