
#include "object.h"

Object::Object(int x, int y, int r, int vmx, const QPixmap *pixmap_, QGraphicsScene *scene_, double v_, int angle_)
    :QGraphicsPixmapItem(pixmap_->scaled(QSize(2*r, 2*r))), v_max(vmx), v(v_), angle(angle_), radius(r){
    setPos(x-r, y-r); // setPos用的是左上角坐标，但是参数x和y是中心坐标，所以要减去偏移。
    scene = scene_;
    scene->addItem(this);
    //isDead = false;
    //setVelocity(0, 0);
}

void Object::change_velocity(double d) {
    if (d>=0) v = min (v_max, v + d);
    else v = max (-v_max, v+d);
}

void Object::change_angle(int d) {
    angle = (360 + angle + d) % 360;
}

void Object::object_update() {
    moveBy(v*cos(angle*3.1415/180), -v*sin(angle*3.1415/180));
    this->setRotation((450-angle)%360);
    update();
}

QPoint Object::get_centre() {
    return QPoint(pos().rx()+radius,pos().ry()+radius);
}



