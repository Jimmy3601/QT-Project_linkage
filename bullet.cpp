
#include "bullet.h"

Bullet::Bullet(int x, int y, double r, int id_, const QPixmap *pixmap_, QGraphicsScene *scene_, double v_, int a_, int d, Player *p):
    Object(x, y, r, v_, id_, pixmap_, scene_, v_, a_), parent(p), damage(d) {
};

Bullet::~Bullet(){

}

void Bullet::object_update(QVector<Object*> & exo) {
    qreal dx = v*cos(angle*3.1415/180), dy = -v*sin(angle*3.1415/180); //dy is -ve cuz +y in qt is in downward direction
    qreal nx = pos().rx() + dx, ny = pos().ry() + dy;
    if (nx>= 0 && ny >= 0 && nx <= 1000-2*radius && ny <= 800 - 2* radius) {//check if inside range
        moveBy(dx, dy);
        update();
    }
    else {
        //qDebug() << "de";
        is_deleted = 1;
    }

}

void Bullet::player_collide(Player *target) {
    if (parent != target) {
        target->on_hurt(damage);
        qDebug() << "shot!";
        is_deleted = 1;
    }
};
