#include "bullet.h"
#include <QGraphicsScene>
#include <QDebug>

Bullet::Bullet(bool playerMade, double x, double y, double size, double scaling)
    :Actor(size, scaling)
{
    movementTimer = new QTimer();
    connect(movementTimer,SIGNAL(timeout()), this, SLOT(move()));
    this->playerMade = playerMade;
    xMove = x * getScaling();
    yMove = y * getScaling();

    movementTimer->start(50);
}

Bullet::Bullet(bool playerMade, double width, double height, double scaling)
    :Actor(width, height, scaling)
{
    movementTimer = new QTimer();
    connect(movementTimer,SIGNAL(timeout()), this, SLOT(move()));
    this->playerMade = playerMade;
    xMove = 0 * getScaling();
    yMove = 10 * getScaling();

    movementTimer->start(55);
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
bool Bullet::getPlayerMade()
{
    return playerMade;
}
