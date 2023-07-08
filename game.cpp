
#include "game.h"
#include <QTimer>
#include <QPainter>
#include <QLinearGradient>
#include <QString>
#include "config.h"
#include "player.h"
#include "bullet.h"
#include "prop.h"
#include <cmath>
#include "choose.h"

//main part of the game
/*NOTES:
 * - pos() represnets the coordinate of the top-left corner of a widget instead of centre
 *
 *
 *
 *
 * */

//QString IMG_SRC = ;


const double deceleration = 0.1;

const int generate_prop_rate = 1200;
const QString buff_description[8] = {"", "Movement speed increased", "Bullet speed increased!", "Rotation speed increased", "Bullet damage increased"
, "Shoot interval decreased", "Gain ability to teleport!", "Heal!"};

Rect *dat[9];



Game::Game(Choose *_p, int _fp1, int _fp2): id_cnt(0), player1_can_shoot(1), player2_can_shoot(1), player1_can_tp(1), player2_can_tp(1), buff_p1(nullptr), buff_p2(nullptr),
    skill1(nullptr),skill1b(nullptr), skill2(nullptr), skill2b(nullptr), faculty_p1(_fp1), faculty_p2(_fp2), parent(_p)
    ,on_cooldown_cnt_p1(0), on_cooldown_cnt_p2(0)
{

}


Game::~Game(){
    delete prop_1_pixmap;
    delete prop_2_pixmap;
    delete player_1_pixmap;
    delete player_2_pixmap;
    delete player1;
    delete player2;
    delete timer;
    delete timer_p1;
    delete timer_p2;
    delete re_p1;
    delete re_p2;
    delete tp_p1;
    delete tp_p2;
    delete prop_timer;
    delete buff_p1;
    delete buff_p2;
    delete currentHealthBar;
    delete currentHealthBar2;
    delete skill1;
    delete skill1b;
    delete skill2;
    delete skill2b;
}

void Game::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    switch (key) {
    case Qt::Key_W:isPressingW = 1; break;
    case Qt::Key_A:isPressingA = 1; break;
    case Qt::Key_S:isPressingS = 1; break;
    case Qt::Key_D:isPressingD = 1; break;
    case Qt::Key_E:isPressingE = 1; break;
    case Qt::Key_Q:isPressingQ = 1; break;
    case Qt::Key_R:isPressingR = 1; break;

    case Qt::Key_Up:isPressingUp = 1; break;
    case Qt::Key_Left:isPressingLeft = 1;break;
    case Qt::Key_Down:isPressingDown = 1;break;
    case Qt::Key_Right:isPressingRight = 1;break;
    case Qt::Key_O:isPressingO = 1; break;
    case Qt::Key_P:isPressingP = 1; break;
    case Qt::Key_I:isPressingI= 1; break;
    }
}

void Game::keyReleaseEvent(QKeyEvent *event){
    auto key = event->key();

    switch(key){
    case Qt::Key_W:isPressingW = 0;break;
    case Qt::Key_A:isPressingA = 0;break;
    case Qt::Key_S:isPressingS = 0;break;
    case Qt::Key_D:isPressingD = 0;break;
    case Qt::Key_E:isPressingE = 0; break;
    case Qt::Key_Q:isPressingQ = 0; break;
    case Qt::Key_R:isPressingR = 0; break;

    case Qt::Key_Up:isPressingUp = 0;break;
    case Qt::Key_Left:isPressingLeft = 0;break;
    case Qt::Key_Down:isPressingDown = 0;break;
    case Qt::Key_Right:isPressingRight = 0;break;
    case Qt::Key_O:isPressingO = 0; break;
    case Qt::Key_P:isPressingP = 0; break;
    case Qt::Key_I:isPressingI = 0; break;
    }
}

void Game::game_start() {
    isPressingA = false;
    isPressingD = false;
    isPressingW = false;
    isPressingS = false;
    isPressingE = false;
    isPressingQ = false;
    isPressingR = false;

    isPressingUp = false;
    isPressingLeft = false;
    isPressingDown = false;
    isPressingRight = false;
    isPressingO = false;
    isPressingP = false;
    isPressingI = false;

    setSceneRect(0,0,MAX_SCREEN_WIDTH,MAX_SCREEN_HEIGHT);
    const QPixmap *cs_pix = new QPixmap(":/menu/res/xk.png");
    const QPixmap *gh_pix = new QPixmap(":/menu/res/gh.png");
    const QPixmap *yp_pix = new QPixmap(":/menu/res/yp.png");
    const QPixmap *xy_pix = new QPixmap(":/menu/res/xy.png");
    prop_1_pixmap = new QPixmap(":/res/prop1.png");
    prop_2_pixmap = new QPixmap(":/res/prop2.png");

    switch(faculty_p1) {
    case 0: player1 = new Eecs(150,465,50, id_cnt++,cs_pix, this, 0); player_1_pixmap = cs_pix; break;
    case 1: player1 = new Guanghua(150,465,50, id_cnt++,gh_pix, this, 0); player_1_pixmap = gh_pix; break;
    case 2: player1 = new Yuanpei(150,465,50, id_cnt++,yp_pix, this, 0); player_1_pixmap = yp_pix; break;
    case 3: player1 = new Xinya(150,465,50, id_cnt++,xy_pix, this, 0); player_1_pixmap = xy_pix; break;
    }

    switch(faculty_p2) {
    case 0: player2 = new Eecs(850,465,50, id_cnt++,cs_pix, this, 180); player_2_pixmap = cs_pix; break;
    case 1: player2 = new Guanghua(850,465,50, id_cnt++,gh_pix, this, 180); player_2_pixmap = gh_pix; break;
    case 2: player2 = new Yuanpei(850,465,50, id_cnt++,yp_pix, this, 180); player_2_pixmap = yp_pix; break;
    case 3: player2 = new Xinya(850,465,50, id_cnt++,xy_pix, this, 180); player_2_pixmap = xy_pix; break;
    }

    existing_objects.append(player1);
    existing_objects.append(player2);

    timer = new QTimer;
    connect(timer,&QTimer::timeout,this, &Game::game_update);
    timer->start(20);

    prop_timer = new QTimer;
    connect(prop_timer,&QTimer::timeout,this, &Game::try_generate_prop);
    prop_timer->start(generate_prop_rate);

    QPixmap pixmap1 = *player_1_pixmap ;
    pixmap1 = pixmap1.scaled(90, 90, Qt::KeepAspectRatioByExpanding);
    QGraphicsPixmapItem *item1 = new QGraphicsPixmapItem(pixmap1);
    item1->setPos(35,0);
    this->addItem(item1);

    QPixmap pixmap4 = *player_2_pixmap;
    pixmap4 = pixmap4.scaled(90, 90, Qt::KeepAspectRatioByExpanding);
    QGraphicsPixmapItem *item4 = new QGraphicsPixmapItem(pixmap4);
    item4->setPos(875,0);
    this->addItem(item4);


    auto txt1 = new QGraphicsTextItem("Buff: ");
    txt1->setDefaultTextColor(Qt::black);
    QFont font("Calibri", 15, QFont::Bold, false);
    txt1->setFont(font);
    txt1->setPos(50, 95);
    addItem(txt1);


    auto txt2 = new QGraphicsTextItem("Buff: ");
    txt2->setDefaultTextColor(Qt::black);
    txt2->setFont(font);
    txt2->setPos(600, 95); //take 50 of width
    addItem(txt2);

    QPen lp;
    lp.setColor(Qt::black);
    this->addLine(0,130,1000,130,lp);
    skill1 = addRect(10, 90, 30, 30);
    QBrush skill_brush;
    skill_brush.setColor(Qt::lightGray);
    skill_brush.setStyle(Qt::SolidPattern);
    skill1->setBrush(skill_brush);

    skill1b = addRect(10, 90, 30, 30);

    QLinearGradient lg(QPointF(10,90), QPointF(40,120));
    lg.setColorAt(0, Qt::red);
    lg.setColorAt(0.4, 0xFFD700);
    lg.setColorAt(0.6, 0xFFD700);
    lg.setColorAt(1.0, Qt::blue);
    //lg.setColorAt(1, 0xA4ABD6);
    QBrush skill1b_brush(lg);
    //skill1b_brush.setColor(0xFFD700);
    //skill1b_brush.setColor(QColorConstants::Svg::aqua);
    //skill1b_brush.setStyle(Qt::SolidPattern);
    skill1b->setBrush(skill1b_brush);

    skill2 = addRect(960, 90, 30, 30);
    skill2->setBrush(skill_brush);

    //130 for status and tips
    QGraphicsRectItem *Wall1 = addRect(150, 250, wallLength, wallThickness);
    QGraphicsRectItem *Wall2 = addRect(150, 250, wallThickness, wallLength);
    QGraphicsRectItem *Wall3 = addRect(150, 680-wallThickness,wallLength ,wallThickness );
    QGraphicsRectItem *Wall4 = addRect(150, 680-wallLength, wallThickness, wallLength);
    QGraphicsRectItem *Wall5 = addRect(850-wallLength, 250,wallLength ,wallThickness );
    QGraphicsRectItem *Wall6 = addRect(850-wallThickness,250, wallThickness, wallLength);
    QGraphicsRectItem *Wall7 = addRect(850-wallLength, 680-wallThickness, wallLength, wallThickness);
    QGraphicsRectItem *Wall8 = addRect(850-wallThickness,680-wallLength, wallThickness,wallLength );
    QGraphicsRectItem *Wall9 = addRect(500-wallThickness/2, 390, wallThickness, wallLength);


    dat[0] = new Rect(150, 250, 1);
    dat[1] = new Rect(150, 250, 0);
    dat[2] = new Rect(150, 680-wallThickness, 1);
    dat[3] = new Rect(150, 680-wallLength, 0);
    dat[4] = new Rect(850-wallLength, 250, 1);
    dat[5] = new Rect(850-wallThickness, 250, 0);
    dat[6] = new Rect(850-wallLength, 680-wallThickness, 1);
    dat[7] = new Rect(850-wallThickness, 680-wallLength, 0);
    dat[8] = new Rect(500-wallThickness/2, 390, 0);
    judge_wall_collision(0,0,0, dat);

    //QGraphicsRectItem *Wall10 = scene->addRect(110, 38, wallLength, wallThickness);

    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);

    Wall1->setBrush(brush);
    Wall2->setBrush(brush);
    Wall3->setBrush(brush);
    Wall4->setBrush(brush);
    Wall5->setBrush(brush);
    Wall6->setBrush(brush);
    Wall7->setBrush(brush);
    Wall8->setBrush(brush);
    Wall9->setBrush(brush);

    //血量条1
    // 创建一个表示总血量的矩形
    QGraphicsRectItem *totalHealthBar = addRect(130, 35, 200, 30);
    QBrush totalBrush;
    totalBrush.setColor(Qt::gray);
    totalBrush.setStyle(Qt::SolidPattern);
    totalHealthBar->setBrush(totalBrush);
    // 创建一个表示当前血量的矩形
    currentHealthBar = addRect(130, 35, 200, 30);
    QBrush currentBrush;
    currentBrush.setColor(Qt::red);
    currentBrush.setStyle(Qt::SolidPattern);
    currentHealthBar->setBrush(currentBrush);

    //血量条2
    // 创建一个表示总血量的矩形
    QGraphicsRectItem *totalHealthBar2 = addRect(670, 35, 200, 30);
    QBrush totalBrush2;
    totalBrush2.setColor(Qt::red);
    totalBrush2.setStyle(Qt::SolidPattern);
    totalHealthBar2->setBrush(totalBrush2);
    // 创建一个表示当前血量的矩形
    currentHealthBar2 = addRect(670, 35, 0, 30);
    QBrush currentBrush2;
    currentBrush2.setColor(Qt::gray);
    currentBrush2.setStyle(Qt::SolidPattern);
    currentHealthBar2->setBrush(currentBrush2);
    //450 0
    QPixmap pixmap6(":/res/vs.png");
    pixmap6 = pixmap6.scaled(100, 100, Qt::KeepAspectRatioByExpanding);
    QGraphicsPixmapItem *item6 = new QGraphicsPixmapItem(pixmap6);
    item6->setPos(450,0);
    addItem(item6);


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
        qreal dx = (player1->radius+12)*cos(player1->angle*3.1415/180), dy = -(player1->radius+12)*sin(player1->angle*3.1415/180); //dy is -ve cuz +y in qt is in downward direction
        qreal nx = player1->get_centre().rx() + dx, ny = player1->get_centre().ry() + dy;

        player1_can_shoot = 0;
        timer_p1 = new QTimer;
        connect(timer_p1,&QTimer::timeout,this, &Game::on_timer_p1);
        timer_p1->start(player1->shoot_interval);
        if (player1->is_using_skill && player1->faculty == 2) {
            for (int j = 0; j != 8; ++j) {
                int angle = (45 * j + player1->angle) % 360;
                qreal dx2 = (player1->radius+12)*cos(angle*3.1415/180), dy2 = -(player1->radius+12)*sin(angle*3.1415/180); //dy is -ve cuz +y in qt is in downward direction
                qreal nx2 = player1->get_centre().rx() + dx2, ny2 = player1->get_centre().ry() + dy2;
                existing_objects.append(new Bullet(nx2, ny2, player1->bullet_radius, id_cnt++, player_1_pixmap, this, player1->bullet_vmax, angle, player1->bullet_damage, player1));
            }
        }
        else if (player1->is_using_skill && player1->faculty == 3) {
            qreal x1 = player1->get_centre().rx(), y1 = player1->get_centre().ry();
            qreal x2 = player2->get_centre().rx(), y2 = player2->get_centre().ry();
            if (1.1*player1->radius+1.1*player2->radius >=  sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))) {
                player2->on_hurt(player1->bullet_damage);
                int rn = rand() % 4;
                if (rn && player1->health < 10) player1->health++;
            }
        }
        else existing_objects.append(new Bullet(nx, ny, player1->bullet_radius, id_cnt++, player_1_pixmap, this, player1->bullet_vmax, player1->angle, player1->bullet_damage, player1));

    }

    if (isPressingO && player2_can_shoot) {
        //qDebug() << "Shooot!";
        qreal dx = (player2->radius+12)*cos(player2->angle*3.1415/180), dy = -(player2->radius+12)*sin(player2->angle*3.1415/180); //dy is -ve cuz +y in qt is in downward direction
        qreal nx = player2->get_centre().rx() + dx, ny = player2->get_centre().ry() + dy;

        player2_can_shoot = 0;

        timer_p2 = new QTimer;
        connect(timer_p2,&QTimer::timeout,this, &Game::on_timer_p2);
        timer_p2->start(player2->shoot_interval);
        if (player2->is_using_skill && player2->faculty == 2) {
            for (int j = 0; j != 8; ++j) {
                int angle = (45 * j + player2->angle) % 360;
                qreal dx2 = (player2->radius+12)*cos(angle*3.1415/180), dy2 = -(player2->radius+12)*sin(angle*3.1415/180); //dy is -ve cuz +y in qt is in downward direction
                qreal nx2 = player2->get_centre().rx() + dx2, ny2 = player2->get_centre().ry() + dy2;
                existing_objects.append(new Bullet(nx2, ny2, player2->bullet_radius, id_cnt++, player_2_pixmap, this, player2->bullet_vmax, angle, player2->bullet_damage, player2));
            }
        }
        else if (player2->is_using_skill && player2->faculty == 3) {
            qreal x1 = player1->get_centre().rx(), y1 = player1->get_centre().ry();
            qreal x2 = player2->get_centre().rx(), y2 = player2->get_centre().ry();
            if (1.1*player1->radius+1.1*player2->radius >=  sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))) {
                player1->on_hurt(player2->bullet_damage);
                int rn = rand() % 4;
                if (rn==0 && player2->health < 10) player2->health++;
            }
        }
        else existing_objects.append(new Bullet(nx, ny, player2->bullet_radius, id_cnt++, player_2_pixmap, this, player2->bullet_vmax, player2->angle, player2->bullet_damage, player2));

    }
    //tp
    if (player1->buff_id == 6 && isPressingR && player1_can_tp) {
        player1->setPos(1000-player1->get_centre().rx()-player1->radius, player1->pos().ry());
        player1_can_tp = 0;
        tp_p1 = new QTimer;
        tp_p1->start(player1->tp_interval);
        connect(tp_p1,&QTimer::timeout,this, &Game::recover_tp_p1);
    }

    if (player2->buff_id == 6 && isPressingI && player2_can_tp) {
        player2->setPos(1000-player2->get_centre().rx()-player2->radius, player2->pos().ry());
        player2_can_tp = 0;
        tp_p2 = new QTimer;
        tp_p2->start(player2->tp_interval);
        connect(tp_p2,&QTimer::timeout,this, &Game::recover_tp_p2);
    }
    //qDebug() << player1->get_centre() << player2->get_centre();

    //try using skill: skill-realated paragraphs should be placed in front of on-hurt animation (due to opacity setting)
    if (isPressingQ && !player1->is_using_skill && player1->skill_duration == 0) {
        player1->use_skill();
        on_cooldown_cnt_p1 = 0;
    }

    if (isPressingP && !player2->is_using_skill && player2->skill_duration == 0) {
        player2->use_skill();
        on_cooldown_cnt_p2 = 0;
    }

    if (player1->skill_duration != 0 && player1->skill_duration % 1000 == 0) {
        double tmp = player1->skill_duration / 1000;
        if (player1->is_using_skill) {
            delete skill1b;
            skill1b = addRect(10, 90 + 30/8.0*(8-tmp), 30, 30/8.0*tmp);
            QBrush skill1b_brush;
            skill1b_brush.setColor(0xFFD700);
            skill1b_brush.setStyle(Qt::SolidPattern);
            skill1b->setBrush(skill1b_brush);
        }
        else {
            delete skill1b;
            skill1b = addRect(10, 90 + 2*tmp, 30, 30-2*tmp);
            QBrush skill1b_brush;
            skill1b_brush.setColor(QColorConstants::Svg::aqua);
            skill1b_brush.setStyle(Qt::SolidPattern);
            skill1b->setBrush(skill1b_brush);
        }
    }

    if (player2->skill_duration != 0 && player2->skill_duration % 1000 == 0) {
        double tmp = player2->skill_duration / 1000;
        if (player2->is_using_skill) {
            delete skill2b;
            skill2b = addRect(960, 90 + 30/8.0*(8-tmp), 30, 30/8.0*tmp);
            QBrush skill2b_brush;
            skill2b_brush.setColor(0xFFD700);
            skill2b_brush.setStyle(Qt::SolidPattern);
            skill2b->setBrush(skill2b_brush);
        }
        else {
            delete skill2b;
            skill2b = addRect(960, 90 + 2*tmp, 30, 30-2*tmp);
            QBrush skill2b_brush;
            skill2b_brush.setColor(QColorConstants::Svg::aqua);
            skill2b_brush.setStyle(Qt::SolidPattern);
            skill2b->setBrush(skill2b_brush);
        }
    }

    if (player1->skill_duration > 0) player1->skill_duration -= 20;
    if (player2->skill_duration > 0) player2->skill_duration -= 20;

    if (player1->is_using_skill && player1->skill_duration==0) {
        player1->skill_expired();
        delete skill1b;
        skill1b = nullptr;
    }
    if (!player1->is_using_skill && player1->skill_duration==0) {
        if (on_cooldown_cnt_p1 % 2000 == 0) {
            delete skill1b;
            skill1b = addRect(10, 90, 30, 30);
            QBrush skill1b_brush;
            skill1b_brush.setColor(0xFFD700);
            skill1b_brush.setStyle(Qt::SolidPattern);
            skill1b->setBrush(skill1b_brush);
        }
        on_cooldown_cnt_p1 += 20;
        int tmp = on_cooldown_cnt_p1 % 2000 - 1500;
        if (tmp >= 0 && tmp % 100 == 0) {
            QLinearGradient lg1(QPointF(10,90), QPointF(40,120));
            int of = (tmp/100);
            lg1.setColorAt(0.1*of, 0xFFD700);
            lg1.setColorAt(0.2+0.1*of, Qt::white);
            lg1.setColorAt(0.4+0.1*of, 0xFFD700);
            QBrush ani1(lg1);
            skill1b->setBrush(ani1);
        }

    }
    if (player2->is_using_skill && player2->skill_duration==0) {
        player2->skill_expired();
        delete skill2b;
        skill2b = nullptr;
    }

    if (!player2->is_using_skill && player2->skill_duration==0) {
        if (on_cooldown_cnt_p2 % 2000 == 0) {
            delete skill2b;
            skill2b = addRect(960, 90, 30, 30);
            QBrush skill2b_brush;
            skill2b_brush.setColor(0xFFD700);
            skill2b_brush.setStyle(Qt::SolidPattern);
            skill2b->setBrush(skill2b_brush);
        }
        on_cooldown_cnt_p2 += 20;
        int tmp = on_cooldown_cnt_p2 % 2000 - 1500;
        if (tmp >= 0 && tmp % 100 == 0) {
            QLinearGradient lg1(QPointF(960,90), QPointF(990,120));
            int of = (tmp/100);
            lg1.setColorAt(0.1*of, 0xFFD700);
            lg1.setColorAt(0.2+0.1*of, Qt::white);
            lg1.setColorAt(0.4+0.1*of, 0xFFD700);
            QBrush ani1(lg1);
            skill2b->setBrush(ani1);
        }


    }

    if (!isPressingW && !isPressingS) {
        player1->v = (player1->v>=0) ? max(0.0, player1->v-deceleration): min(0.0, player1->v+deceleration);  
    }
    if (!isPressingUp && !isPressingDown) {
         player2->v = (player2->v>=0) ? max(0.0, player2->v-deceleration): min(0.0, player2->v+deceleration);
    }
    player1->object_update(existing_objects,dat);
    player2->object_update(existing_objects,dat);

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

    if (player1->buff_id != 0 && player1->buff_duration % 1000 == 0) {
         delete buff_p1;
         QString tmp = buff_description[player1->buff_id];
         tmp += "  ";
         tmp += QString::number(player1->buff_duration / 1000, 10);
         tmp += " s";
         QFont font("Calibri", 15, QFont::Bold, false);
         buff_p1 = new QGraphicsTextItem(tmp);
         buff_p1->setPos(100, 95);
         buff_p1->setFont(font);        
         if (player1->is_buff_rare) buff_p1->setDefaultTextColor(0xCFB53B);
         else buff_p1->setDefaultTextColor(Qt::black);
         addItem(buff_p1);
    }

    if (player1->buff_duration > 0) player1->buff_duration -=  20;
    else {
         player1->remove_buff();
         delete buff_p1;
         buff_p1 = nullptr;
    }

    if (player2->buff_id != 0 && player2->buff_duration % 1000 == 0) {
         delete buff_p2;
         QString tmp = buff_description[player2->buff_id];
         tmp += "  ";
         tmp += QString::number(player2->buff_duration / 1000, 10);
         tmp += " s";
         QFont font("Calibri", 15, QFont::Bold, false);
         buff_p2 = new QGraphicsTextItem(tmp);
         buff_p2->setPos(650, 95);
         buff_p2->setFont(font);
         if (player2->is_buff_rare) buff_p2->setDefaultTextColor(0xCFB53B);
         else buff_p2->setDefaultTextColor(Qt::black);
         addItem(buff_p2);
    }

    if (player2->buff_duration > 0) player2->buff_duration -=  20;
    else {
         player2->remove_buff();
         delete buff_p2;
         buff_p2 = nullptr;
    }

    //update qvector
    for (int i = 2; i != existing_objects.size(); ++i) {
         auto p = existing_objects[i];
         p->object_update(existing_objects, dat);
         if (p->is_deleted) {
            existing_objects.removeAt(i);
            delete p;
             --i;
         }
    }

    //update health bar
    delete currentHealthBar;
    delete currentHealthBar2;
    currentHealthBar = addRect(130, 35, 20*player1->health, 30);
    QBrush currentBrush;
    currentBrush.setColor(Qt::red);
    currentBrush.setStyle(Qt::SolidPattern);
    currentHealthBar->setBrush(currentBrush);

    currentHealthBar2 = addRect(670, 35, 200-20*player2->health, 30);
    QBrush currentBrush2;
    currentBrush2.setColor(Qt::gray);
    currentBrush2.setStyle(Qt::SolidPattern);
    currentHealthBar2->setBrush(currentBrush2);

    //check if game end
    if (player1->is_deleted) {
         timer->stop();
         //if (player2->is_deleted) {
          //   qDebug() << "Game Draw!";
         //}
         qDebug() << "Player 2 win!";
         parent->game_end(1);


    }
    else if (player2->is_deleted) {
         timer->stop();
         qDebug() << "Player 1 win!";
         parent->game_end(0);
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
    if (player1->faculty == 0 && player1->is_using_skill) player1->setOpacity(0.5);
    else player1->setOpacity(1.0);
    re_p1->stop();
}

void Game::recover_opacity_p2() {
    if (player2->faculty == 0 && player2->is_using_skill) player2->setOpacity(0.5);
    else player2->setOpacity(1.0);
    re_p2->stop();
}

void Game::recover_tp_p1() {
    player1_can_tp = 1;
    tp_p1->stop();
}

void Game::recover_tp_p2() {
    player2_can_tp = 1;
    tp_p2->stop();
}

void Game::try_generate_prop() {
    int x = 30 + ceil(rand()%910);
    int y = 160 + ceil(rand()%600);
    if (existing_objects.size() < 5 && abs(player1->get_centre().rx()- x) > 100 && abs(player1->get_centre().ry()- y) > 90 && abs(player2->get_centre().rx()- x) > 100 && abs(player2->get_centre().ry()- y) > 90) {
         if (rand()%10<9)
            existing_objects.append(new Prop(x, y, 20, id_cnt++, prop_1_pixmap, this, 0));
         else  existing_objects.append(new Prop(x, y, 20, id_cnt++, prop_2_pixmap, this, 1));
         update();
    }

}


