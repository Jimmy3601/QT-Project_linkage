
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
#include <QVector>



class Game: public QGraphicsScene
{
    Q_OBJECT
public:

    friend class Player;
    friend class Object;

    Game();
    //~Game();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
public slots:
    void game_start();
    void game_update();
    void on_timer_p1();
    void on_timer_p2();

private:
    //clock/time
    QTimer *timer, *timer_p1, *timer_p2;
    int T;
    long long global_time;


    //objects
    Object *player1, *player2;
    QVector<Object*> existing_objects; //storing all existing objects (players, bullets, items...)
    bool player1_can_shoot, player2_can_shoot;
    int id_cnt;

    bool isPressingW,isPressingA,isPressingS,isPressingD, isPressingE;
    bool isPressingUp,isPressingDown,isPressingLeft,isPressingRight, isPressingO;

    bool check_collisions(Object);
    void try_shoot(Player &player);
    //void add_plyaers();
};

#endif // GAME_H
