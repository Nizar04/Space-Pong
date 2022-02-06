#ifndef BALL_H
#define BALL_H

#include <QWidget>
#include <QPainter>

class ball : public QWidget
{
    Q_OBJECT
public:
    explicit ball(QWidget *parent = nullptr)  ;
    QRect    shape()                          ;

private:
    QWidget *p;
    const int ballspeed = 10 ; //control ball speed
    const int ballshape = 13 ; //control the size of the ball
    int x                    ;
    int y                    ;
    int moveX = ballspeed    ;
    int moveY = ballspeed    ;
signals:
    void ball_Moves(QRect &ball)            ;
    void Scored(bool who)                   ;
public slots:
    void Ball_Move()                        ;
    void Ball_Draw(QPainter &painter)       ;
    void Ball_Reset()                       ;
    void Ball_Bounce(int type)              ;
};
#endif // BALL_H
