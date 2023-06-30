#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    int cnt;
    ~Dialog();

private slots:
    void on_NextButton1_clicked();

private:
    Ui::Dialog *ui;
    QImage bg[3]={QImage{":/res/intr1.png"},QImage{":/res/intr2.png"},QImage{":/res/intr3.png"}};
};

#endif // DIALOG_H
