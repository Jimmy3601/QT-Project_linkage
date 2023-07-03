
#include "player.h"
#include <QTimer>

const int SPACING = 20; //cuz the image files contain some empty space

Player::Player(int x, int y, int r,int id_, const QPixmap *pixmap_, QGraphicsScene *scene_, int initial_angle):
    Object(x,y,r,3, id_, pixmap_, scene_, 0, initial_angle), health(10), health_max(10), is_hurt(0)
{
    shoot_interval = 1000;
}

void Player::shoot() {

}
void Player::object_update(QList<Object*> & exo) {
    bool collision = 0;
    int si = exo.size();
    qreal dx = v*cos(angle*3.1415/180), dy = -v*sin(angle*3.1415/180); //dy is -ve cuz +y in qt is in downward direction
    qreal nx = get_centre().rx() + dx, ny = get_centre().ry() + dy;
    for (int i = 0; i !=si; ++i) {
        Object *other = exo[i];
        if (other!=this) {
            if (other->is_circle) {
                qreal x2 = other->get_centre().rx(), y2 = other->get_centre().ry();
                if (0.8*this->radius+0.8*other->radius >=  sqrt((nx-x2)*(nx-x2)+(ny-y2)*(ny-y2))) {
                    collision = 1;
                    other->player_collide(this);
                }
                //qDebug() << "collision:" << self->get_centre();
            }

        }

    }
    if (nx>= radius && ny >= radius && nx <= 1000-radius && ny <= 800 - radius && !collision) //check if inside range
        moveBy(dx, dy);
    this->setRotation((450-angle)%360);
    update();
}

void Player::on_hurt(int damage) {
    health -= damage;
    setOpacity(0.2);
    is_hurt = 1;
    qDebug() << health;
    if (health <= 0) {
        qDebug() << "player"<<id+1<< "died!";
        is_deleted = 1;
    }
}

void Player::use_skill() {

}


