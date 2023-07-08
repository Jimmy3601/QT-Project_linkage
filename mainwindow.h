
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include "dialog.h"
#include <QPainter>
#include "choose.h"

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

    int cntBGM;

private slots:

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
