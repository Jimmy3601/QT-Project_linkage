
#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"



class Player: public Object
{

public:
    Player(int x, int y, int r, const QPixmap *pixmap_, QGraphicsScene *scene_, int initial_angle);
    //~Player();

};

#endif // PLAYER_H
