
#include "player.h"

const int SPACING = 20; //cuz the image files contain some empty space

Player::Player(int x, int y, int r,int id_, const QPixmap *pixmap_, QGraphicsScene *scene_, int initial_angle): Object(x,y,r,3, id_, pixmap_, scene_, 0, initial_angle), health(10), health_max(10)
{

}

void Player::shoot() {

}

void Player::object_update(const QVector<Object*> & exo) {
    bool collision = 0;
    int si = exo.size();
    qreal dx = v*cos(angle*3.1415/180), dy = -v*sin(angle*3.1415/180); //dy is -ve cuz +y in qt is in downward direction
    qreal nx = pos().rx() + dx, ny = pos().ry() + dy;
    for (int i = 0; i !=si; ++i) {
        Object *other = exo[i];
        if (other!=this) {
            if (other->is_circle) {
                qreal x2 = other->pos().rx(), y2 = other->pos().ry();
                if (this->radius+this->radius-SPACING >=  sqrt((nx-x2)*(nx-x2)+(ny-y2)*(ny-y2))) collision = 1;
                //qDebug() << "collision:" << self->get_centre();
            }

        }

    }
    if (nx>= 0 && ny >= 0 && nx <= 1000-2*radius && ny <= 800 - 2* radius && !collision) //check if inside range
        moveBy(dx, dy);
    this->setRotation((450-angle)%360);
    update();
}

void Player::on_hurt(int damage) {

}



