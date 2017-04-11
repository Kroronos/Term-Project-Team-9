#include "bullet.h"
#include <QGraphicsScene>
#include <QDebug>

Bullet::Bullet(bool playerMade, double x, double y)
    :Actor(-2,-2,2)
{
    movementTimer = new QTimer();
    connect(movementTimer,SIGNAL(timeout()), this, SLOT(move()));
    this->playerMade = playerMade;
    xMove = x;
    yMove = y;

    movementTimer->start(50);
}

Bullet::Bullet(bool playerMade, double x, double y, double distortion)
    :Actor(-2,-2,2, distortion)
{
    movementTimer = new QTimer();
    connect(movementTimer,SIGNAL(timeout()), this, SLOT(move()));
    this->playerMade = playerMade;
    xMove = x * distortion;
    yMove = y * distortion;

    movementTimer->start(50);
}

void Bullet::move()
{
    //Move away from player
    if(playerMade){
        setPos(x()+xMove,y()-yMove);
        //Delete bullets when they leave upper region
        if(pos().y() < 0 - y()){
            scene()->removeItem(this);
            delete this;
        }
    }
    //Move towards player
    else {
       setPos(x()+xMove,y()+yMove);
       //Delete bullets when they leave bottom region
       if(pos().y() > scene()->height()){
           scene()->removeItem(this);
           delete this;
       }
    }
}
