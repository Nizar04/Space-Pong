#include "ball.h"

ball::ball(QWidget *parent) : QWidget(parent)
{ // Proprities
    p = parent;
    x = p->rect().width()/2;
    y = p->rect().height()/2;

}
QRect ball::shape()
{
    QRect out(x,y,ballshape,ballshape);
    return out;
}
void ball::Ball_Move()// Responsible for the way the ball gonna move
{
    if(x <= 0){
        emit Scored(true);
    }else if(x+ballshape >= p->rect().width()){
        emit Scored(false);
    }
    if(y <= 0 || y+ballshape >= p->rect().height())moveY *= -1;

    x += moveX;
    y += moveY;

    QRect myRect(x,y,ballshape,ballshape);
    emit ball_Moves(myRect);
}
void ball::Ball_Draw(QPainter &painter)//responsible for drawing the ball
{ painter.drawEllipse(x,y,ballshape,ballshape);//function used to the ball within the specified proprities mentioned in .h file
}
void ball::Ball_Reset() // Responsble for recentring the ball within the screen after a scored point
{
    x = p->rect().width()/2   ;
    y = p->rect().height()/2  ;
    if(rand()%2){
    moveX = ballspeed  ;
    moveY = ballspeed  ;
    }
    else{
    moveX = -1*ballspeed ;
    moveY = -1*ballspeed ;
    }
}
void ball::Ball_Bounce(int type) // Responsible for the way the way the ball gonna rebound after a colision
{
    switch (type) {
    case 0:
        moveX *= -1.5           ;
        moveY =  -1*(moveY+1)   ;
        x += moveX              ;
        y += moveY              ;
        break;

    case 1:
        moveX *= -1            ;
        moveY =  -1*(moveY+6)  ;
        x += moveX             ;
        y += moveY             ;
        break;
    default:
        break;
    }
}

