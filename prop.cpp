
#include "prop.h"

Prop::Prop(int x, int y, double r, int id_, const QPixmap *pixmap_, QGraphicsScene *scene_, bool rare):
    Object(x, y, r, 0, id_, pixmap_, scene_, 0, 90), is_rare(rare) {

};

void Prop::player_collide(Player *target) {
    int i = 1 + rand() % 7;
    target->grant_buff(i, 1);
    is_deleted = 1;
}

