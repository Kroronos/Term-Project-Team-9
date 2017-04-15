#include "player.h"
#include "actor.h"
#include "bullet.h"
#include <QKeyEvent>
#include <QtCore>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <QTimerEvent>
#include <QGraphicsPixmapItem>

//Player Constructor
Player::Player(const QString &fileName, double scaling)
    : Actor(fileName, scaling)
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

    equippedWeapon = new Weapon(500, this, 3, scaling);
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

void Player::decrementHealth()
{
    --health;
}

void Player::incrementHealth()
{
    ++health;
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
            if(x()>0) {
                setPos(x()-25*getScaling(), y());
                ++movedLeft;
                if(!(hasMovedLeft)) {
                    //Change to first left step
                    timesMovedConsecutivelyInDirection = 0;
                }
            }
            if(movedLeft >= 1) {
                ++timesMovedConsecutivelyInDirection;
                movedRight = 0;
                movedUp = 0;
                movedDown = 0;
                if(!(hasMovedRight)) {
                    switch(movedLeft)
                    {
                        case 1: setPixmap(QPixmap(":/Images/Images/Player_Turn_Left1.png"));
                            break;
                        case 2:setPixmap(QPixmap(":/Images/Images/Player_Turn_Left2.png"));
                            break;
                        case 3:setPixmap(QPixmap(":/Images/Images/Player_Turn_Left3.png"));
                            break;
                        case 4:setPixmap(QPixmap(":/Images/Images/Player_Turn_Left4.png"));
                            break;
                        case 5:setPixmap(QPixmap(":/Images/Images/Player_Turn_Left5.png"));
                            break;
                        case 6:setPixmap(QPixmap(":/Images/Images/Player_Turn_Left6.png"));
                            break;
                        case 7:setPixmap(QPixmap(":/Images/Images/Player_Turn_Left7.png"));
                            break;
                        case 8:setPixmap(QPixmap(":/Images/Images/Player_Turn_Left8.png"));
                            break;
                        case 9:setPixmap(QPixmap(":/Images/Images/Player_Turn_Left9.png"));
                            break;
                        case 10:setPixmap(QPixmap(":/Images/Images/Player_Turn_Left10.png"));
                            break;
                        case 11:setPixmap(QPixmap(":/Images/Images/Player_Turn_Left11.png"));
                            break;
                    }
                }
            }
            hasMovedLeft = true;
        }
        //Move right
        if((k == moveRight || k == moveRight2) && !hasMovedRight) {
            //Check to see if player is off screen region
            if(x() + getWidth() < scene()->width()) {
                setPos(x()+25*getScaling(), y());
                ++movedRight;
                if(!(hasMovedLeft)) {
                    //Change to first right step
                    timesMovedConsecutivelyInDirection = 0;
                }
            }
            if(movedRight >= 1) {
                ++timesMovedConsecutivelyInDirection;
                movedLeft = 0;
                movedUp = 0;
                movedDown = 0;
                if(!(hasMovedLeft)) {
                    switch(movedRight) {
                    case 1:setPixmap(QPixmap(":/Images/Images/Player_Turn_Right1.png"));
                        break;
                    case 2:setPixmap(QPixmap(":/Images/Images/Player_Turn_Right2.png"));
                        break;
                    case 3:setPixmap(QPixmap(":/Images/Images/Player_Turn_Right3.png"));
                        break;
                    case 4:setPixmap(QPixmap(":/Images/Images/Player_Turn_Right4.png"));
                        break;
                    case 5:setPixmap(QPixmap(":/Images/Images/Player_Turn_Right5.png"));
                        break;
                    case 6:setPixmap(QPixmap(":/Images/Images/Player_Turn_Right6.png"));
                        break;
                    case 7:setPixmap(QPixmap(":/Images/Images/Player_Turn_Right7.png"));
                        break;
                    case 8:setPixmap(QPixmap(":/Images/Images/Player_Turn_Right8.png"));
                        break;
                    case 9:setPixmap(QPixmap(":/Images/Images/Player_Turn_Right9.png"));
                        break;
                    case 10:setPixmap(QPixmap(":/Images/Images/Player_Turn_Right10.png"));
                        break;
                    case 11:setPixmap(QPixmap(":/Images/Images/Player_Turn_Right11.png"));
                        break;
                    }
                }
            }
            hasMovedRight = true;
        }
        //Move up
        if((k == moveUp || k == moveUp2) && !hasMovedUp) {
            //Check to see if player is off screen region
            if(y() - getHeight()/8 > 0){
                setPos(x(), y()-25*getScaling());
                ++movedUp;
                if(!(hasMovedLeft || hasMovedRight)) {
                    //Change to first up step
                    timesMovedConsecutivelyInDirection = 0;
                }
            }
            if(movedUp >= 1) {
                ++timesMovedConsecutivelyInDirection;
                movedRight = 0;
                movedLeft = 0;
                movedDown = 0;
                if(!(hasMovedLeft || hasMovedRight)) {
                    switch(moveUp) {
                    case 1:setPixmap(QPixmap(":/Images/Images/Player_Straight8.png"));
                        break;
                    case 2:setPixmap(QPixmap(":/Images/Images/Player_Straight9.png"));
                        break;
                    case 3:setPixmap(QPixmap(":/Images/Images/Player_Straight10.png"));
                        break;
                    case 4:setPixmap(QPixmap(":/Images/Images/Player_Straight11.png"));
                        break;
                    case 5:setPixmap(QPixmap(":/Images/Images/Player_Straight12.png"));
                        break;
                    case 6:setPixmap(QPixmap(":/Images/Images/Player_Straight13.png"));
                        break;
                    case 7:setPixmap(QPixmap(":/Images/Images/Player_Straight14.png"));
                        break;
                    case 8:setPixmap(QPixmap(":/Images/Images/Player_Straight15.png"));
                        break;
                    case 9:setPixmap(QPixmap(":/Images/Images/Player_Straight16.png"));
                        break;
                    case 10:setPixmap(QPixmap(":/Images/Images/Player_Straight17.png"));
                        break;
                    case 11:setPixmap(QPixmap(":/Images/Images/Player_Straight18.png"));
                        break;
                    }
                }
            }
            hasMovedUp = true;
        }
        //Move down
        if((k == moveDown || k == moveDown2) && !hasMovedDown) {
            //Check to see if player is off screen region
            if(y()+getHeight() < scene()->height()) {
                setPos(x(), y()+25*getScaling());
                ++movedDown;
                if(movedDown == 0) {
                    ++movedDown;
                    if(!(hasMovedLeft || hasMovedRight)) {
                        //Change to first down step
                        timesMovedConsecutivelyInDirection = 0;
                    }
                }
                if(movedDown >= 1) {
                    if(!(hasMovedLeft || hasMovedRight)) {
                        ++timesMovedConsecutivelyInDirection;
                        movedRight = 0;
                        movedUp = 0;
                        movedLeft = 0;
                        switch(movedDown) {
                        case 1:setPixmap(QPixmap(":/Images/Images/Player_Straight8.png"));
                            break;
                        case 2:setPixmap(QPixmap(":/Images/Images/Player_Straight9.png"));
                            break;
                        case 3:setPixmap(QPixmap(":/Images/Images/Player_Straight10.png"));
                            break;
                        case 4:setPixmap(QPixmap(":/Images/Images/Player_Straight11.png"));
                            break;
                        case 5:setPixmap(QPixmap(":/Images/Images/Player_Straight12.png"));
                            break;
                        case 6:setPixmap(QPixmap(":/Images/Images/Player_Straight13.png"));
                            break;
                        case 7:setPixmap(QPixmap(":/Images/Images/Player_Straight14.png"));
                            break;
                        case 8:setPixmap(QPixmap(":/Images/Images/Player_Straight15.png"));
                            break;
                        case 9:setPixmap(QPixmap(":/Images/Images/Player_Straight16.png"));
                            break;
                        case 10:setPixmap(QPixmap(":/Images/Images/Player_Straight17.png"));
                            break;
                        case 11:setPixmap(QPixmap(":/Images/Images/Player_Straigh18.png"));
                            break;
                        }
                    }
                }
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


