
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QKeyEvent>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QMessageBox>
#include <QString>
#include <QTimer>
#include <QTime>
#include <QDebug>
//#include <QMediaPlayer>
#include <QMainWindow>
<<<<<<< HEAD
//#include <QMediaPlaylist>
=======
#include <QDockWidget>
#include "dialog.h"
#include <QPainter>
>>>>>>> aafef4bed2366b4f6b314dc199cc99c9276c6451

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);

private slots:
    void on_QuitButton_clicked();
    void on_IntroButton_clicked();

    void on_Start_game_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
