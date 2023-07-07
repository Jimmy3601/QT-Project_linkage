
#ifndef GAME_H
#define GAME_H

#include <QKeyEvent>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QGraphicsTextItem>
#include <QMessageBox>
#include <QString>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include "object.h"
#include <algorithm>
#include <cmath>
#include <QList>



class Game: public QGraphicsScene
{
    Q_OBJECT
public:

    friend class Player;
    friend class Object;
    friend class Bullet;

    Game();

    //~Game();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
public slots:
    void game_start();
    void game_update();
    void on_timer_p1();
    void on_timer_p2();
    void recover_opacity_p1();
    void recover_opacity_p2();
    void recover_tp_p1();
    void recover_tp_p2();
    void try_generate_prop();
    void try_trigger_event();

private:
    QGraphicsTextItem *buff_p1, *buff_p2;
    QGraphicsRectItem *currentHealthBar, *currentHealthBar2, *skill1, *skill1b, *skill2, *skill2b;
    //clock/time
    QTimer *timer, *timer_p1, *timer_p2, *re_p1, *re_p2, *tp_p1, *tp_p2, *prop_timer, *event_timer;
    int T;
    long long global_time;


    //objects
    Player *player1, *player2;
    QList<Object*> existing_objects; //storing all existing objects (players, bullets, items...)
    bool player1_can_shoot, player2_can_shoot, player1_can_tp, player2_can_tp;
    int id_cnt;

    bool isPressingW,isPressingA,isPressingS,isPressingD, isPressingE, isPressingQ, isPressingR;
    bool isPressingUp,isPressingDown,isPressingLeft,isPressingRight, isPressingO, isPressingP, isPressingI;

    //void add_plyaers();

};

#endif // GAME_H
