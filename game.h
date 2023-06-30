
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

private:
    //clock/time
    QTimer *timer;
    int T;
    long long global_time;

    //objects
    Object *player1, *player2;
    QVector<Object*> existing_objects; //storing all existing objects (players, bullets, items...)


    bool isPressingW,isPressingA,isPressingS,isPressingD;
    bool isPressingUp,isPressingDown,isPressingLeft,isPressingRight;

    bool check_collisions(Object *self);

    //void add_plyaers();
};

#endif // GAME_H
