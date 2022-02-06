#ifndef PADDLE_H
#define PADDLE_H

#include <QWidget>
#include <QPainter>

class paddle : public QWidget
{
    Q_OBJECT
public://
    explicit paddle(QWidget *parent = nullptr,bool player = true);
    QRect Shape()       ;
    void  padReset() ; //Responsible for resetting paddle Position after a win

private:
//Constants and Variables responsible for paddle proprities
    QWidget *p = NULL ;
    bool     human    ;

    const int buffer = 5     ;
          int posXBack       ;
          int posYBack       ;
          int positionX      ;
          int positionY       ;

    const int pWidth = 15    ;//Paddle Width
    const int pHeight = 120  ;//Paddle Height
    const int AIspeed = 10   ;// Variable responsible for the movement speed of the AI controlled paddle

          void CheckCol() ;
public slots: //Functions of the paddles
          void Paddraw(QPainter &painter)  ;
          void Padmove(QPoint &pos)        ;
          void AIAlgo(QRect &ball)           ;
};

#endif // PADDLE_H
