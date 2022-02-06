#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QPixmap>
#include "ball.h"
#include "paddle.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0); ~MainWindow();

private:

    int playerScore               ;//counter for Player Score
    int enemyScore                ;//counter for AI Score
    int firstTime = 1             ;// Condition for opening dialog box
    const int maxScore = 10       ;// limit that each player gonna score
    QWidget         *p      ;
    paddle          *player ;
    paddle          *enemy  ;
    ball            *myBall ;
    Ui::MainWindow  *ui     ;
    QTimer          *timer  ;
    bool running = false    ;

    void resetGame()    ;
    void VictoryCheck() ;

protected: //Declaring Functions
    virtual void mousePressEvent(QMouseEvent *e)        ;
    virtual void paintEvent(QPaintEvent *)              ;
    virtual void mouseMoveEvent(QMouseEvent *e)         ;
    virtual void mouseDoubleClickEvent(QMouseEvent *)   ;

signals:
    void Draw(QPainter &painter)   ;
    void Pos_Report(QPoint &pos)    ;
    void W_bounce(int choose)        ;

public slots:
    void Scored(bool who)  ;

private slots:
    void colisionDet()  ;


};

#endif // MAINWINDOW_H
