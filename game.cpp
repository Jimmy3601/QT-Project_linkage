
#include "game.h"
#include <QTimer>
#include <QPainter>
#include "config.h"
#include "player.h"

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
    case Qt::Key_E:isPressingE = 1; break;

    case Qt::Key_Up:isPressingUp = false;break;
    case Qt::Key_Left:isPressingLeft = false;break;
    case Qt::Key_Down:isPressingDown = false;break;
    case Qt::Key_Right:isPressingRight = false;break;
    case Qt::Key_O:isPressingE = 1; break;
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
    qDebug() << existing_objects.size();
    timer = new QTimer;
    connect(timer,&QTimer::timeout,this, &Game::game_update);
    timer->start(20);
    player1->setTransformOriginPoint(50, 50);
    player2->setTransformOriginPoint(50, 50);


}

void Game::game_update() {
    if (isPressingW) player1->change_velocity(1);
    if (isPressingA) player1->change_angle(5);
    if (isPressingS) player1->change_velocity(-1);
    if (isPressingD) player1->change_angle(-5);
    if (isPressingUp) player2->change_velocity(1);
    if (isPressingLeft) player2->change_angle(5);
    if (isPressingDown) player2->change_velocity(-1);
    if (isPressingRight) player2->change_angle(-5);

    if (isPressingE && player1_can_shoot) {

    }
    //qDebug() << player1->get_centre() << player2->get_centre();

    if (!isPressingW && !isPressingS) {
        player1->v = (player1->v>=0) ? max(0.0, player1->v-deceleration): min(0.0, player1->v+deceleration);
        player2->v = (player2->v>=0) ? max(0.0, player2->v-deceleration): min(0.0, player2->v+deceleration);
    }
    player1->object_update(existing_objects);
    player2->object_update(existing_objects);
}

bool Game::check_collisions(Object) {
    bool ans = 0;

    return ans;
}

void Game::on_timer_p1() {

}

void Game::on_timer_p2() {

}

void Game::try_shoot(Player & player) {

}
