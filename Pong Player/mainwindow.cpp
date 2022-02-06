#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "time.h"
#include <QMediaPlayer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(NULL));
    //playing background music
    QMediaPlayer *music = new QMediaPlayer ;
    music->setMedia(QUrl(":/images/Backgroundplayer.mp3"));
    music->play();

    playerScore = 0  ; // setting the variable playerscore
    enemyScore  = 0  ; //setting the variable enemyscore

    centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents) ;
    setMouseTracking(true) ;                                           // used as a part of the mouse tracking

    p = parent               ;
    setFixedSize(1920,1080)  ;                                                        // setting the window size the specified resolution
    move(QApplication::desktop()->screen()->rect().center()-this->rect().center())  ;
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint)                   ;
/* Declarations */
    timer  = new QTimer(this)       ;
    myBall = new ball(this)         ;
    player = new paddle(this,true)  ;
    enemy  = new paddle(this,false) ;
/* Connections */
    QObject::connect(timer,SIGNAL(timeout()), this,SLOT(repaint()))                    ;
    QObject::connect(timer,&QTimer::timeout, myBall, &ball::Ball_Move)                 ;
    QObject::connect(timer,&QTimer::timeout, this , &MainWindow::colisionDet)    ;

    QObject::connect(myBall,&ball::ball_Moves,enemy,&paddle::AIAlgo)                   ;

    QObject::connect(this,&MainWindow::Draw, myBall ,&ball::Ball_Draw)                  ;
    QObject::connect(this,&MainWindow::Draw, player ,&paddle::Paddraw)              ;
    QObject::connect(this,&MainWindow::Draw, enemy  ,&paddle::Paddraw)              ;

    QObject::connect(this,&MainWindow::Pos_Report, player, &paddle::Padmove)         ;
    QObject::connect(this,&MainWindow::W_bounce,    myBall, &ball::Ball_Bounce)               ;

    QObject::connect(myBall,&ball::Scored, this, &MainWindow::Scored)                  ;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetGame()      //Responsible for the game reset after after winning or loosing
{
    myBall  ->  Ball_Reset()    ;  //resets the ball position
    player  ->  padReset()  ;  //reset player paddle position
    enemy   ->  padReset()  ;  //reset enemy paddle  position
    playerScore  =  0          ;  //resets score
    enemyScore   =  0          ;  //reset score
    timer   ->  stop()         ;  //stopping timer
    running      = false       ;
    this    ->  update()       ;

}

void MainWindow::VictoryCheck()   //checks for victory or lost to reset game and display appropriate dialog
{
    if     (playerScore  >= maxScore){ //win case
       QMessageBox::information(this,"YOU", "WON"); //message box for informing
       resetGame(); // resets game
    }
    else if(enemyScore   >= maxScore){ // lose case
       QMessageBox::information(this,"YOU","LOST"); // message box for informing
       resetGame();
    }

}

void MainWindow::mousePressEvent(QMouseEvent *e)// Starting the game when clicking left
{
    if       (e->button() == Qt::LeftButton && running == false){
             timer    ->    start(16);
             running   =   true;
    }
    else if  (e->button() == Qt::LeftButton && running == true){
             timer    ->   stop();
             running  =    false;
    }
}

void MainWindow::paintEvent(QPaintEvent *) // Graphical Part
{
    QPainter painter(this);

    painter.fillRect(rect(),QPixmap(":/images/pics2.png"));  // Setting the background image


    painter.setPen(Qt::white)                             ;
    painter.setBrush(QBrush(QColor(Qt::white)))           ;

     QString pl  =  "PLAYER  "  +QString::number(playerScore)  ; // Display text + player score

     QString ai  =  "COMPUTER " +QString::number(enemyScore)   ; // Dispaly text + enemey score
     painter.drawText(480,50,pl)   ;
     painter.drawText(1440,50,ai)  ;

    emit Draw(painter)  ;

    if(firstTime == 1){ // checks if its the first time the game launches
        QMessageBox::information(this,"SPACE PONG","CLICK TO START THE YOUR SPACE JOURNEY .\n "," START .\n ")  ; // Greeting and explaining dialog
        firstTime --  ;
    }

}

void MainWindow::mouseMoveEvent(QMouseEvent *e)//Resposible for mouse tracking wich is used to control the paddle vertical mouvement
{
    QPoint point  =  e  ->  pos()  ;
    emit   Pos_Report(point)        ;
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *) // Responsible for reseting the game after a double click event
{
    resetGame()  ;
}

void MainWindow::Scored(bool who) // responsible for keeping tracks of the score
{
    if(who){ // enemy score incrementation
        enemyScore++  ;
        myBall  ->  Ball_Reset()  ;
    }
    else{
        playerScore++  ;   // player score incrementation
        myBall  ->  Ball_Reset()  ;
    }
    VictoryCheck()  ; // checks for lose or win case to reset game and display appropiate messages

}

void MainWindow::colisionDet() // responsible for the collison detection
{

    if(myBall->shape().x() < player->Shape().x()+player->Shape().width() && myBall->shape().y()+myBall->shape().height() > player->Shape().y() && myBall->shape().y() < player->Shape().y()+player->Shape().height())emit W_bounce(rand()%2);
    if(myBall->shape().x()+myBall->shape().width() > enemy->Shape().x() && myBall->shape().y()+myBall->shape().height() > enemy->Shape().y() && myBall->shape().y() < enemy->Shape().y()+enemy->Shape().height())emit W_bounce(rand()%2);

}

