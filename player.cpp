#include "player.h"
#include "actor.h"
#include "bullet.h"
#include <QKeyEvent>
#include <QtCore>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <QTimerEvent>

//Player Triangle Constructor
Player::Player(double vertexA, double vertexB, double vertexC, double scaling)
    : Actor(vertexA, vertexB, vertexC, scaling)
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

    equippedWeapon = new Weapon(this, double(5), scaling);
}

//Player Rectangle Constructor
Player::Player(double vertexA, double vertexB, double scaling)
    : Actor(vertexA, vertexB, scaling)
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

    equippedWeapon = new Weapon(this, double(5), scaling);
}

//Player Circle Constructor
Player::Player(double radius, double scaling)
    : Actor(radius, scaling)
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

    equippedWeapon = new Weapon(this, double(10), scaling);
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
    if((Qt::Key)event->key() == shoot){
        equippedWeapon->setCanFire(false);
    }
}

void Player::setMoveUp(Qt::Key a)
{
    moveUp = a;
}

void Player::setMoveUp2(Qt::Key a)
{
    moveUp2 = a;
}

void Player::setMoveDown(Qt::Key a)
{
    moveDown = a;
}

void Player::setMoveDown2(Qt::Key a)
{
    moveDown2 = a;
}

void Player::setMoveLeft(Qt::Key a)
{
    moveLeft = a;
}

void Player::setMoveLeft2(Qt::Key a)
{
    moveLeft2 = a;
}

void Player::setMoveRight(Qt::Key a)
{
    moveRight = a;
}

void Player::setMoveRight2(Qt::Key a)
{
    moveRight2 = a;
}

void Player::setShoot(Qt::Key a)
{
    shoot = a;
}

int Player::getHealth()
{
    return health;
}

void Player::setHealth(int a)
{
    health = a;
}

//Acts on a timer interval for each key pressed
//Increments through every key pressed and performs appropriate actions

//Fast actions include movement
void Player::keyPressFastAction()
{
    //used to control user from inputing both possible move keys to extract double effect
    bool hasMovedLeft = false;
    bool hasMovedRight = false;
    bool hasMovedUp = false;
    bool hasMovedDown = false;

    foreach(Qt::Key k, keysPressed){

        //Move left
        if((k == moveLeft || k == moveLeft2) && !hasMovedLeft) {
            //Check to see if player is off screen region
            if(x() - getWidth() >0) {
                setPos(x()-25*getScaling(), y());
            }
            hasMovedLeft = true;
        }
        //Move right
        if((k == moveRight || k == moveRight2) && !hasMovedRight) {
            //Check to see if player is off screen region
            if(x() + getWidth() < scene()->width()) {
                setPos(x()+25*getScaling(), y());
            }
            hasMovedRight = true;
        }
        //Move up
        if((k == moveUp || k == moveUp2) && !hasMovedUp) {
            //Check to see if player is off screen region
            if(y()-getHeight() > 0){
                setPos(x(), y()-25*getScaling());
            }
            hasMovedUp = true;
        }
        //Move down
        if((k == moveDown || k == moveDown2) && !hasMovedDown) {
            //Check to see if player is off screen region
            if(y()+getHeight() < scene()->height()) {
                setPos(x(), y()+25*getScaling());
            }
            hasMovedDown = true;
        }

        if(k == shoot){
            equippedWeapon->setCanFire(true);
        }
    }
}

//Slow actions, actions we don't want to instantly and immediately respond to player input
void Player::keyPressSlowAction()
{

}


