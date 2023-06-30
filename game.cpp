
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

Game::Game()
{

}

void Game::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    switch (key) {
    case Qt::Key_W:isPressingW = 1; break;
    case Qt::Key_A:isPressingA = 1; break;
    case Qt::Key_S:isPressingS = 1; break;
    case Qt::Key_D:isPressingD = 1; break;

    case Qt::Key_Up:isPressingUp = 1; break;
    case Qt::Key_Left:isPressingLeft = 1;break;
    case Qt::Key_Down:isPressingDown = 1;break;
    case Qt::Key_Right:isPressingRight = 1;break;
    }
}

void Game::keyReleaseEvent(QKeyEvent *event){
    auto key = event->key();

    switch(key){
    case Qt::Key_W:isPressingW = false;break;
    case Qt::Key_A:isPressingA = false;break;
    case Qt::Key_S:isPressingS = false;break;
    case Qt::Key_D:isPressingD = false;break;
    case Qt::Key_Up:isPressingUp = false;break;
    case Qt::Key_Left:isPressingLeft = false;break;
    case Qt::Key_Down:isPressingDown = false;break;
    case Qt::Key_Right:isPressingRight = false;break;
    }
}

void Game::game_start() {
    isPressingA = false;
    isPressingD = false;
    isPressingW = false;
    isPressingS = false;
    isPressingUp = false;
    isPressingLeft = false;
    isPressingDown = false;
    isPressingRight = false;

    setSceneRect(0,0,MAX_SCREEN_WIDTH,MAX_SCREEN_HEIGHT);
    player_1_pixmap = new QPixmap(":/menu/res/qygh.png");
    player_2_pixmap = new QPixmap(":/menu/res/qygh.png");
    player1 = new Player(MAX_SCREEN_WIDTH/4,MAX_SCREEN_HEIGHT/2,50,player_1_pixmap,this, 0);
    player2 = new Player(3*MAX_SCREEN_WIDTH/4,MAX_SCREEN_HEIGHT/2,50, player_2_pixmap,this,180);
    existing_objects.append(player1);
    existing_objects.append(player2);

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
    qDebug() << player1->get_centre() << player2->get_centre();

    if (!isPressingW && !isPressingS) {
        player1->v = (player1->v>=0) ? max(0.0, player1->v-deceleration): min(0.0, player1->v+deceleration);
        player2->v = (player2->v>=0) ? max(0.0, player2->v-deceleration): min(0.0, player2->v+deceleration);
    }
    player1->object_update();
    player2->object_update();
}

bool Game::check_collisions(Object *self) {
    return 0;
}
