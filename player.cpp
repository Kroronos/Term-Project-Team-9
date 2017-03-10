#include "player.h"
#include "actor.h"
#include "bullet.h"
#include <QKeyEvent>
#include <QtCore>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <QTimerEvent>

Player::Player(double vertexA, double vertexB, double vertexC)
    : Actor(vertexA, vertexB, vertexC)
{

    //Makes Player allowed to become focusable
    setFlag(QGraphicsItem::ItemIsFocusable);
    //Allows Player to receive input
    setFocus();

    //Initialize timers
    fastTimer = new QTimer();
    slowTimer = new QTimer();

    //Connect timers to respective slots
    connect(fastTimer,SIGNAL(timeout()), this, SLOT(keyPressFastAction()));
    connect(slowTimer,SIGNAL(timeout()), this, SLOT(keyPressSlowAction()));

    //Set interval and start timers
    //50 ms interval for smooth movement NOTE: this should probably be synch to monitor refresh rate instead of being a timer
    fastTimer-> start(50);
    //500 ms interval updates every half second
    slowTimer-> start(500);

    equippedWeapon = new Weapon(500, this, 5);
}

//Adds Keys Pressed By Player To A Set
void Player::keyPressEvent(QKeyEvent* event)
{
    keysPressed += (Qt::Key)event->key();
}

//Removes Keys Released By Player from Set
void Player::keyReleaseEvent(QKeyEvent* event)
{
    keysPressed -= (Qt::Key)event->key();
    if((Qt::Key)event->key() == Qt::Key_Space){
        equippedWeapon->setCanFire(false);
    }
}

//Acts on a timer interval for each key pressed
//Increments through every key pressed and performs appropriate actions

//Fast actions include movement
void Player::keyPressFastAction()
{
    foreach(Qt::Key k, keysPressed){
        //Move left
        if(k == Qt::Key_A) {
            //Check to see if player is off screen region
            if(x() - getWidth() >0) {
                setPos(x()-10, y());
            }
        }
        //Move right
        if(k == Qt::Key_D) {
            //Check to see if player is off screen region
            if(x() + getWidth() < scene()->width()) {
                setPos(x()+10, y());
            }
        }
        //Move up
        if(k == Qt::Key_W) {
            //Check to see if player is off screen region
            if(y()-getHeight() > 0){
                setPos(x(), y()-10);
            }
        }
        //Move down
        if(k == Qt::Key_S) {
            //Check to see if player is off screen region
            if(y()+getHeight() < scene()->height()) {
                setPos(x(), y()+10);
            }
        }

        if(k == Qt::Key_Space){
            equippedWeapon->setCanFire(true);
        }
    }
}

//Slow actions, actions we don't want to instantly and immediately respond to player input
void Player::keyPressSlowAction()
{

}


