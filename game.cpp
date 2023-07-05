
#include "game.h"
#include <QTimer>
#include <QPainter>
#include "config.h"
#include "player.h"
#include "bullet.h"
#include "prop.h"
#include <cmath>

//main part of the game
/*NOTES:
 * - pos() represnets the coordinate of the top-left corner of a widget instead of centre, regardless of rotation.
 *
 *
 *
 *
 * */

//QString IMG_SRC = ;
QPixmap *player_1_pixmap, *player_2_pixmap;
const double deceleration = 0.1;
const int generate_prop_rate = 15000;

Game::Game(): id_cnt(0), player1_can_shoot(1), player2_can_shoot(1)
{

}

void Game::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    switch (key) {
    case Qt::Key_W:isPressingW = 1; break;
    case Qt::Key_A:isPressingA = 1; break;
    case Qt::Key_S:isPressingS = 1; break;
    case Qt::Key_D:isPressingD = 1; break;
    case Qt::Key_E:isPressingE = 1; break;

    case Qt::Key_Up:isPressingUp = 1; break;
    case Qt::Key_Left:isPressingLeft = 1;break;
    case Qt::Key_Down:isPressingDown = 1;break;
    case Qt::Key_Right:isPressingRight = 1;break;
    case Qt::Key_O:isPressingO = 1; break;
    }
}

void Game::keyReleaseEvent(QKeyEvent *event){
    auto key = event->key();

    switch(key){
    case Qt::Key_W:isPressingW = false;break;
    case Qt::Key_A:isPressingA = false;break;
    case Qt::Key_S:isPressingS = false;break;
    case Qt::Key_D:isPressingD = false;break;
    case Qt::Key_E:isPressingE = 0; break;

    case Qt::Key_Up:isPressingUp = false;break;
    case Qt::Key_Left:isPressingLeft = false;break;
    case Qt::Key_Down:isPressingDown = false;break;
    case Qt::Key_Right:isPressingRight = false;break;
    case Qt::Key_O:isPressingO = 0; break;
    }
}

void Game::game_start() {
    isPressingA = false;
    isPressingD = false;
    isPressingW = false;
    isPressingS = false;
    isPressingE = false;
    isPressingUp = false;
    isPressingLeft = false;
    isPressingDown = false;
    isPressingRight = false;
    isPressingO = false;

    setSceneRect(0,0,MAX_SCREEN_WIDTH,MAX_SCREEN_HEIGHT);
    player_1_pixmap = new QPixmap(":/menu/res/qygh.png");
    player_2_pixmap = new QPixmap(":/menu/res/qygh.png");
    player1 = new Player(MAX_SCREEN_WIDTH/4,MAX_SCREEN_HEIGHT/2,50, id_cnt++,player_1_pixmap,this, 0);
    player2 = new Player(3*MAX_SCREEN_WIDTH/4,MAX_SCREEN_HEIGHT/2,50, id_cnt++, player_2_pixmap,this,180);
    existing_objects.append(player1);
    existing_objects.append(player2);

    timer = new QTimer;
    connect(timer,&QTimer::timeout,this, &Game::game_update);
    timer->start(20);

    prop_timer = new QTimer;
    connect(prop_timer,&QTimer::timeout,this, &Game::try_generate_prop);
    prop_timer->start(generate_prop_rate);


}

void Game::game_update() {
    //key responding

    if (isPressingW) player1->change_velocity(1);
    if (isPressingA) player1->change_angle(player1->angular_velocity);
    if (isPressingS) player1->change_velocity(-1);
    if (isPressingD) player1->change_angle(-player1->angular_velocity);
    if (isPressingUp) player2->change_velocity(1);
    if (isPressingLeft) player2->change_angle(player2->angular_velocity);
    if (isPressingDown) player2->change_velocity(-1);
    if (isPressingRight) player2->change_angle(-player2->angular_velocity);

    if (isPressingE && player1_can_shoot) {
        qDebug() << "Shooot!";
        qreal dx = (player1->radius+12)*cos(player1->angle*3.1415/180), dy = -(player1->radius+12)*sin(player1->angle*3.1415/180); //dy is -ve cuz +y in qt is in downward direction
        qreal nx = player1->get_centre().rx() + dx, ny = player1->get_centre().ry() + dy;
        existing_objects.append(new Bullet(nx, ny, 10, id_cnt++, player_1_pixmap, this, player1->bullet_vmax, player1->angle, player1->bullet_damage, player1));
        //qDebug() << existing_objects[id_cnt-1]->get_centre();

        player1_can_shoot = 0;
        timer_p1 = new QTimer;
        connect(timer_p1,&QTimer::timeout,this, &Game::on_timer_p1);
        timer_p1->start(player1->shoot_interval);
    }

    if (isPressingO && player2_can_shoot) {
        qDebug() << "Shooot!";
        qreal dx = (player2->radius+12)*cos(player2->angle*3.1415/180), dy = -(player2->radius+12)*sin(player2->angle*3.1415/180); //dy is -ve cuz +y in qt is in downward direction
        qreal nx = player2->get_centre().rx() + dx, ny = player2->get_centre().ry() + dy;

        existing_objects.append(new Bullet(nx, ny, 10, id_cnt++, player_2_pixmap, this, player2->bullet_vmax, player2->angle, player2->bullet_damage, player2));
        player2_can_shoot = 0;

        timer_p2 = new QTimer;
        connect(timer_p2,&QTimer::timeout,this, &Game::on_timer_p2);
        timer_p2->start(player2->shoot_interval);
    }
    //qDebug() << player1->get_centre() << player2->get_centre();

    if (!isPressingW && !isPressingS) {
        player1->v = (player1->v>=0) ? max(0.0, player1->v-deceleration): min(0.0, player1->v+deceleration);  
    }
    if (!isPressingUp && !isPressingDown) {
         player2->v = (player2->v>=0) ? max(0.0, player2->v-deceleration): min(0.0, player2->v+deceleration);
    }
    player1->object_update(existing_objects);
    player2->object_update(existing_objects);

    if (player1->is_hurt) {
         player1->is_hurt = 0;
         re_p1 = new QTimer;
         connect(re_p1,&QTimer::timeout,this, &Game::recover_opacity_p1);
         re_p1->start(150);
    }

    if (player2->is_hurt) {
         player2->is_hurt = 0;
         re_p2 = new QTimer;
         connect(re_p2,&QTimer::timeout,this, &Game::recover_opacity_p2);
         re_p2->start(150);
    }

    if (player1->buff_duration > 0) player1->buff_duration -=  20;
    else player1->remove_buff();

    if (player2->buff_duration > 0) player2->buff_duration -=  20;
    else player2->remove_buff();


    //update qvector
    for (int i = 2; i != existing_objects.size(); ++i) {
         auto p = existing_objects[i];
         p->object_update(existing_objects);
         if (p->is_deleted) {
            existing_objects.removeAt(i);
            delete p;
             --i;
         }
    }

    //check if game end
    if (player1->is_deleted) {
         timer->stop();
         if (player2->is_deleted) {
             qDebug() << "Game Draw!";
         }
         else qDebug() << "Player 2 win!";
    }
    else if (player2->is_deleted) {
         timer->stop();
         qDebug() << "Player 1 win!";
    }

}

void Game::on_timer_p1() {
    timer_p1->stop();
    player1_can_shoot = 1;
}

void Game::on_timer_p2() {
    timer_p2->stop();
    player2_can_shoot = 1;
}

void Game::recover_opacity_p1() {
    player1->setOpacity(1.0);
    re_p1->stop();
}

void Game::recover_opacity_p2() {
    player2->setOpacity(1.0);
    re_p2->stop();
}

void Game::try_generate_prop() {
    int x = 30 + ceil(rand()%940);
    int y = 30 + ceil(rand()%740);
    if (existing_objects.size() < 5 && abs(player1->get_centre().rx()- x) > 100 && abs(player1->get_centre().ry()- y) > 90 && abs(player2->get_centre().rx()- x) > 100 && abs(player2->get_centre().ry()- y) > 90) {
         existing_objects.append(new Prop(x, y, 20, id_cnt++, player_1_pixmap, this, 0));
         qDebug() << x << ' ' <<y << "Prop generation succeed";
         update();
    }

}

void Game::try_trigger_event() {

}

