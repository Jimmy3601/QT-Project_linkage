
#ifndef BULLET_H
#define BULLET_H

#include "object.h"


class Bullet//: public Object
{
    int damage;
public:
    Bullet();
    Player *parent;

};

#endif // BULLET_H
