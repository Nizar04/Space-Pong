#include "paddle.h"

paddle::paddle(QWidget *parent, bool player) : QWidget(parent)
{
    p     = parent  ;
    human = player  ;
    if(human == true){
        positionX     =  buffer ;
        positionY     =  p->rect().height()/2 - pHeight/2  ;
        posXBack      =  positionX   ;
        posYBack      =  positionY   ;
    }else{
        positionX     =  p->rect().width() - buffer - pWidth       ; //setting constant position that splits the UI IN HALF Horizontally
        positionY     =  p->rect().height()/2-pHeight/2            ; //setting constant position that splits the UI IN HALF Vertically
        posXBack      =  positionX                                 ; // Horizontal position that the paddle gonna take after a scored point
        posYBack      =  positionY                                 ; // Vertical   position that the paddle gonna take after a scored point
    }

}
QRect paddle::Shape()//Responsible for the Paddle shape
{
    QRect out(positionX,positionY,pWidth,pHeight)  ;
    return out  ;
}
 void paddle::padReset()//Responsible for reseting the paddle into their initial position after scored Point
{
    positionX = posXBack ;
    positionY = posYBack ;
}
 void paddle::CheckCol() // checks the pads position to not go over the ui limits
{
    if(positionY < 0)positionY = 0                                                    ;
    if(positionY+pHeight > p->rect().height())positionY = p->rect().height()-pHeight  ;
}
 void paddle::Paddraw(QPainter &painter)
{
    painter.drawRect(positionX,positionY,pWidth,pHeight)  ;//Function that draws the paddles within the specified proprities

}
 void paddle::Padmove(QPoint &pos)// Respoonsible for the player controlled movement of the paddle
{
  positionY = pos.y() - (pHeight/2) ;
  CheckCol()        ;
}
 void paddle::AIAlgo(QRect &ball) // Responsible for moving the "computer Controlled" paddle within the vertical axis depending on the ball vertical axis coordinates
{
    if(ball.y() > positionY+pHeight/2)positionY += AIspeed  ;   //moves the ball depending on the constant set on the .h file
    if(ball.y() < positionY+pHeight/2)positionY -= AIspeed  ;
    CheckCol()      ; // keeps on checking for the pad to not go over the ui limits
}

