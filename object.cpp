
#include "object.h"

bool judge_wall_collision(int x, int y, int r, Rect** rect) {
    bool ans = 0;
    for (int i = 0; i != 9; ++i) {
        Rect *p = *(rect+i);
        double x1 = p->x, y1 = p->y;
        double w =  (p->is_horizontal) ? wallLength: wallThickness, h = (p->is_horizontal) ? wallThickness: wallLength;
        double x2 = p->x + w, y2 = y1, x3 = x1, y3 = y1 + h, x4 = x2, y4 = y3;
        if (x >= x1 && x <= x2 && y>=y1-r && y<=y3+r) {
            ans = 1; break;
        }
        else if (y >= y1 && y<= y3 && x>=x1-r && x<=x2+r) {
            ans = 1; break;
        }
        else if (r >= sqrt((x1-x)*(x1-x)+(y1-y)*(y1-y))) {
            ans = 1; break;
        }
        else if (r >= sqrt((x2-x)*(x2-x)+(y2-y)*(y2-y))) {
            ans = 1; break;
        }
        else if (r >= sqrt((x3-x)*(x3-x)+(y3-y)*(y3-y))) {
            ans = 1; break;
        }
        else if (r >= sqrt((x4-x)*(x4-x)+(y4-y)*(y4-y))) {
            ans = 1; break;
        }
    }

    return ans;
};


Object::Object(int x, int y, double r, double vmx, int id_, const QPixmap *pixmap_, QGraphicsScene *scene_, double v_, int angle_)
    :QGraphicsPixmapItem(pixmap_->scaled(QSize(2*r, 2*r))), v_max(vmx), v(v_), angle(angle_), radius(r), x_size(0), y_size(0), id(id_), is_circle(1), is_deleted(0), angular_velocity(5){
    setPos(x-r, y-r); // setPos uses the coordinate of the top-left corner of the object
    setTransformOriginPoint(r,r);
    scene = scene_;
    scene->addItem(this);
}


Object::Object(int x, int y, double sx, double sy, int vmx, int id_, const QPixmap *pixmap_, QGraphicsScene *scene_, double v_, int angle_)
    :QGraphicsPixmapItem(pixmap_->scaled(QSize(2*sx, 2*sy))), v_max(vmx), v(v_), angle(angle_), radius(0), x_size(sx), y_size(sy), is_circle(0), id(id_), is_deleted(0),angular_velocity(5){
    setPos(x-sx, y-sy); // setPos uses the coordinate of the top-left corner of the object
    scene = scene_;
    scene->addItem(this);
    setTransformationMode(Qt::SmoothTransformation);
    //isDead = false;
}


void Object::change_velocity(double d) {
    if (d>=0) v = min (v_max, v + d);
    else v = max (-v_max, v+d);
}

void Object::change_angle(int d) {
    angle = (360 + angle + d) % 360;
}

void Object::object_update(QList<Object*> & exo, Rect **rect) {
    qreal dx = v*cos(angle*3.1415/180), dy = -v*sin(angle*3.1415/180); //dy is -ve cuz +y in qt is in downward direction
    qreal nx = get_centre().rx() + dx, ny = get_centre().ry() + dy;
    if (nx>= PIX_MULTIPLIER*radius && ny >= 130+PIX_MULTIPLIER*radius && nx <= 1000-PIX_MULTIPLIER*radius && ny <= 800 - PIX_MULTIPLIER*radius) //check if inside range
        moveBy(dx, dy);
    this->setRotation((450-angle)%360);
    update();
}

bool Object::operator == (const Object &other) {
    return id == other.id;
}

bool Object::operator != (const Object &other) {
    return id != other.id;
}

Object::operator int() {
    return id;
}

QPoint Object::get_centre() {
    return QPoint(pos().rx()+radius,pos().ry()+radius);
}

void Object::player_collide(Player *target) {

}



