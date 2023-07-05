
#include "player.h"
#include <QTimer>

const int SPACING = 20; //cuz the image files contain some empty space

Player::Player(int x, int y, int r,int id_, const QPixmap *pixmap_, QGraphicsScene *scene_, int initial_angle):
    Object(x,y,r,3, id_, pixmap_, scene_, 0, initial_angle), health(10), health_max(10), is_hurt(0), buff_id(0),
    buff_duration(0), shoot_interval(1000), bullet_vmax(12), bullet_damage(1), is_buff_rare(0)
{

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

void Player::grant_buff(int _id, bool _is_rare) {

    remove_buff();
    buff_id = _id, is_buff_rare = _is_rare;
    buff_duration = 10000;
    int multiplier = (_is_rare)? 5:2;
    /*buff list(id)
     * 0: none
     * 1: gain 66%/150% extra movement speed
     * 2: gain 100%/400% extra bullet speed
     * 3: gain 100%/400% extra rotation speed
     * 4: bullet deal 100%/300% extra damage
     * 5: shoot interval beecome 0.4/0.1 s
     * 6: sneaking: has 50%/80% chances
     * 7: instant effect: heal 1/4 health
     * */
    qDebug() << "Buff! id:" << _id;
    switch(buff_id) {
    case 1: v_max = v_max / 3 * (3+multiplier); break;
    case 2: bullet_vmax *= multiplier; break;
    case 3: angular_velocity *= multiplier; break;
    case 4: bullet_damage *= multiplier; break;
    case 5: (shoot_interval *= (6-multiplier)) /= 10; break;
    case 6: setScale(1.0/multiplier); break;
    case 7: buff_id = 0, buff_duration = 0, is_buff_rare = 0, health = max(health-1+multiplier, health_max); break;
    }
}

void Player::remove_buff() { 
    int multiplier = (is_buff_rare)? 5:2;
    switch(buff_id) {
    case 1: v_max = v_max * 3 / (3+multiplier); break;
    case 2: bullet_vmax /= multiplier; break;
    case 3: angular_velocity /= multiplier; break;
    case 4: bullet_damage /= multiplier; break;
    case 5: (shoot_interval /= (6-multiplier)) *= 10; break;
    case 6: setScale(1.0); break;
    }
    buff_id = 0, buff_duration = 0, is_buff_rare = 0;
}


