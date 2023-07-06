
#include "player.h"
#include <QTimer>

const int SPACING = 20; //cuz the image files contain some empty space
const int MAX_SKILL_USE_DURATION = 8000;
const int MAX_SKILL_COOLDOWN_DURATION = 15000;
const double PIX_MULTIPLIER = 0.9;


Player::Player(int x, int y, int r,int id_, const QPixmap *pixmap_, QGraphicsScene *scene_, int initial_angle, int _f):
    Object(x,y,r,3, id_, pixmap_, scene_, 0, initial_angle), health(10), health_max(10), is_hurt(0), buff_id(0), faculty(_f),
    buff_duration(0), shoot_interval(1000), bullet_vmax(12), bullet_damage(1), bullet_radius(10), is_buff_rare(0), is_using_skill(0), skill_duration(0)
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
    if (nx>= PIX_MULTIPLIER*radius && ny >= 130+PIX_MULTIPLIER*radius && nx <= 1000-PIX_MULTIPLIER*radius && ny <= 800 - PIX_MULTIPLIER*radius && !collision) //check if inside range
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
        health = 0;
        qDebug() << "player"<<id+1<< "died!";
        is_deleted = 1;
    }
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
     * 6: 0.5/0.2 scale
     * 7: instant effect: heal 1/4 health
     * */
    qDebug() << "Buff! id:" << _id;
    switch(buff_id) {
    case 1: v_max = v_max / 3 * (3+multiplier); break;
    case 2: bullet_vmax *= multiplier; break;
    case 3: angular_velocity *= multiplier; break;
    case 4: bullet_damage *= multiplier; break;
    case 5: (shoot_interval *= (6-multiplier)) /= 10; break;
    case 6: setScale(1.0/multiplier); radius/=multiplier; break;
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
    case 6: setScale(1.0); radius *= multiplier;  break;
    }
    buff_id = 0, buff_duration = 0, is_buff_rare = 0;
}

void Player::use_skill() {
    is_using_skill = 1;
    skill_duration = MAX_SKILL_USE_DURATION;
}

void Player::skill_expired() {
    is_using_skill = 0;
    skill_duration = MAX_SKILL_USE_DURATION;
}

Eecs::Eecs(int x, int y, int r, int id_,const QPixmap *pixmap, QGraphicsScene *scene_, int initial_angle):Player(x, y, r, id_,pixmap, scene_,initial_angle, 0) {};
void Eecs::use_skill() {
    is_using_skill = 1;
    skill_duration = MAX_SKILL_USE_DURATION;
    setOpacity(0.5);
}
void Eecs::skill_expired() {
    is_using_skill = 0;
    skill_duration = MAX_SKILL_COOLDOWN_DURATION;
    setOpacity(1.0);
}

void Eecs::on_hurt(int damage) {
    int rn = 0;
    if (is_using_skill) rn = rand() % 100;
    if (rn < 20) {
        health -= (is_using_skill) ? 1 : damage;
        setOpacity(0.2);
        is_hurt = 1;
        qDebug() << health;
        if (health <= 0) {
            health = 0; //added for ensuring health bar displaying correct
            qDebug() << "player"<<id+1<< "died!";
            is_deleted = 1;
        }
    }
}


Guanghua::Guanghua(int x, int y, int r, int id_,const QPixmap *pixmap, QGraphicsScene *scene_, int initial_angle):Player(x, y, r, id_,pixmap, scene_,initial_angle, 1){};
void Guanghua::use_skill() {
    is_using_skill = 1;
    skill_duration = MAX_SKILL_USE_DURATION;
    bullet_radius *= 2;
    bullet_damage *= 2;
}
void Guanghua::skill_expired() {
    is_using_skill = 0;
    skill_duration = MAX_SKILL_COOLDOWN_DURATION;
    bullet_radius /= 2;
    bullet_damage /= 2;
}

Yuanpei::Yuanpei(int x, int y, int r, int id_,const QPixmap *pixmap, QGraphicsScene *scene_, int initial_angle):Player(x, y, r, id_, pixmap, scene_,initial_angle, 2) {};


Xinya::Xinya(int x, int y, int r, int id_,const QPixmap *pixmap, QGraphicsScene *scene_, int initial_angle):Player(x, y, r, id_, pixmap, scene_,initial_angle, 3) {};
void Xinya::use_skill() {
    is_using_skill = 1;
    skill_duration = MAX_SKILL_USE_DURATION;
    shoot_interval /= 2;
    v_max *= 2;
}

void Xinya::skill_expired() {
    is_using_skill = 0;
    skill_duration = MAX_SKILL_COOLDOWN_DURATION;
    shoot_interval *= 2;
    v_max /= 2;
}
