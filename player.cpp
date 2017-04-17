#include "player.h"
#include "actor.h"
#include "bullet.h"
#include "enemy.h"
#include "enemyone.h"
#include "enemytwo.h"
#include "enemythree.h"
#include "enemyfour.h"

#include <QKeyEvent>
#include <QtCore>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <QTimerEvent>
#include <QGraphicsPixmapItem>

//Player Constructor
Player::Player(const QString &fileName, double scaling)
    : Actor(fileName, scaling * 0.65)
{

    this->scaling = scaling * 0.65;
    realScaling = scaling;
    health = new Health();
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

    equippedWeapon = new Weapon(400, this, nullptr, 3, scaling);
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
        equippedWeapon->softSetCanFire(false);
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

void Player::startFastTimer()
{
    fastTimer->start();
}

void Player::stopFastTimer()
{
    fastTimer->stop();
}

int Player::getHealth()
{
    return health->getHealth();
}

void Player::decrementHealth()
{
    health->decrease();
}

void Player::incrementHealth()
{
    health->increase();
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
                setPos(x()-25*realScaling, y());
                ++movedLeft;
            }
            if(movedLeft >= 1) {
                movedRight = 0;
                movedUp = 0;
                movedDown = 0;
                if(!(hasMovedRight)) {
                    switch(movedLeft)
                    {
                        case 1: setPixmap(QPixmap(":/Images/Images/Player_Turn_Left1.png").scaled(QPixmap(":/Images/Images/Player_Turn_Left1.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Left1.png").height()* scaling));
                            break;
                        case 2:setPixmap(QPixmap(":/Images/Images/Player_Turn_Left2.png").scaled(QPixmap(":/Images/Images/Player_Turn_Left2.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Left2.png").height()* scaling));
                            break;
                        case 3:setPixmap(QPixmap(":/Images/Images/Player_Turn_Left3.png").scaled(QPixmap(":/Images/Images/Player_Turn_Left3.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Left3.png").height()* scaling));
                            break;
                        case 4:setPixmap(QPixmap(":/Images/Images/Player_Turn_Left4.png").scaled(QPixmap(":/Images/Images/Player_Turn_Left4.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Left4.png").height()* scaling));
                            break;
                        case 5:setPixmap(QPixmap(":/Images/Images/Player_Turn_Left5.png").scaled(QPixmap(":/Images/Images/Player_Turn_Left5.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Left5.png").height()* scaling));
                            break;
                        case 6:setPixmap(QPixmap(":/Images/Images/Player_Turn_Left6.png").scaled(QPixmap(":/Images/Images/Player_Turn_Left6.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Left6.png").height()* scaling));
                            break;
                        case 7:setPixmap(QPixmap(":/Images/Images/Player_Turn_Left7.png").scaled(QPixmap(":/Images/Images/Player_Turn_Left7.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Left7.png").height()* scaling));
                            break;
                        case 8:setPixmap(QPixmap(":/Images/Images/Player_Turn_Left8.png").scaled(QPixmap(":/Images/Images/Player_Turn_Left8.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Left8.png").height()* scaling));
                            break;
                        case 9:setPixmap(QPixmap(":/Images/Images/Player_Turn_Left9.png").scaled(QPixmap(":/Images/Images/Player_Turn_Left9.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Left9.png").height()* scaling));
                            break;
                        case 10:setPixmap(QPixmap(":/Images/Images/Player_Turn_Left10.png").scaled(QPixmap(":/Images/Images/Player_Turn_Left10.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Left10.png").height()* scaling));
                            break;
                        case 11:setPixmap(QPixmap(":/Images/Images/Player_Turn_Left11.png").scaled(QPixmap(":/Images/Images/Player_Turn_Left11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Left11.png").height()* scaling));
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
                setPos(x()+25*realScaling, y());
                ++movedRight;
            }
            if(movedRight >= 1) {
                movedLeft = 0;
                movedUp = 0;
                movedDown = 0;
                if(!(hasMovedLeft)) {
                    switch(movedRight) {
                    case 1:setPixmap(QPixmap(":/Images/Images/Player_Turn_Right1.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right1.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right1.png").height()* scaling));
                        break;
                    case 2:setPixmap(QPixmap(":/Images/Images/Player_Turn_Right2.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right2.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right2.png").height()* scaling));
                        break;
                    case 3:setPixmap(QPixmap(":/Images/Images/Player_Turn_Right3.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right3.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right3.png").height()* scaling));
                        break;
                    case 4:setPixmap(QPixmap(":/Images/Images/Player_Turn_Right4.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right4.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right4.png").height()* scaling));
                        break;
                    case 5:setPixmap(QPixmap(":/Images/Images/Player_Turn_Right5.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right5.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right5.png").height()* scaling));
                        break;
                    case 6:setPixmap(QPixmap(":/Images/Images/Player_Turn_Right6.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right6.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right6.png").height()* scaling));
                        break;
                    case 7:setPixmap(QPixmap(":/Images/Images/Player_Turn_Right7.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right7.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right7.png").height()* scaling));
                        break;
                    case 8:setPixmap(QPixmap(":/Images/Images/Player_Turn_Right8.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right8.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right8.png").height()* scaling));
                        break;
                    case 9:setPixmap(QPixmap(":/Images/Images/Player_Turn_Right9.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right9.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right9.png").height()* scaling));
                        break;
                    case 10:setPixmap(QPixmap(":/Images/Images/Player_Turn_Right10.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right10.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right10.png").height()* scaling));
                        break;
                    case 11:setPixmap(QPixmap(":/Images/Images/Player_Turn_Right11.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                        break;
                    }
                }
            }
            hasMovedRight = true;
        }
        //Move up
        //Changed up and down scalars to be equal to those of the horizontal axis
        if((k == moveUp || k == moveUp2) && !hasMovedUp) {
            //Check to see if player is off screen region
            if(y() - getHeight()/8 > 0){
                setPos(x(), y()-25*realScaling);
                ++movedUp;
            }
            if(movedUp >= 1) {
                movedRight = 0;
                movedLeft = 0;
                movedDown = 0;
                if(!(hasMovedLeft || hasMovedRight)) {
                    switch(movedUp) {
                    case 1:
                        setPixmap(QPixmap(":/Images/Images/Player_Straight8.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                        break;
                    case 2:setPixmap(QPixmap(":/Images/Images/Player_Straight9.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                        break;
                    case 3:setPixmap(QPixmap(":/Images/Images/Player_Straight10.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                        break;
                    case 4:setPixmap(QPixmap(":/Images/Images/Player_Straight11.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                        break;
                    case 5:setPixmap(QPixmap(":/Images/Images/Player_Straight12.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                        break;
                    case 6:setPixmap(QPixmap(":/Images/Images/Player_Straight13.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                        break;
                    case 7:setPixmap(QPixmap(":/Images/Images/Player_Straight14.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                        break;
                    case 8:setPixmap(QPixmap(":/Images/Images/Player_Straight15.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                        break;
                    case 9:setPixmap(QPixmap(":/Images/Images/Player_Straight16.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                        break;
                    case 10:setPixmap(QPixmap(":/Images/Images/Player_Straight17.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                        break;
                    case 11:setPixmap(QPixmap(":/Images/Images/Player_Straight18.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                        movedUp = 0;
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
                setPos(x(), y()+25*realScaling);
                ++movedDown;
                }
                if(movedDown >= 1) {
                    if(!(hasMovedLeft || hasMovedRight)) {
                        movedRight = 0;
                        movedUp = 0;
                        movedLeft = 0;
                        switch(movedDown) {
                            case 1:
                                setPixmap(QPixmap(":/Images/Images/Player_Straight8.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                                break;
                            case 2:setPixmap(QPixmap(":/Images/Images/Player_Straight9.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                                break;
                            case 3:setPixmap(QPixmap(":/Images/Images/Player_Straight10.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                                break;
                            case 4:setPixmap(QPixmap(":/Images/Images/Player_Straight11.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                                break;
                            case 5:setPixmap(QPixmap(":/Images/Images/Player_Straight12.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                                break;
                            case 6:setPixmap(QPixmap(":/Images/Images/Player_Straight13.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                                break;
                            case 7:setPixmap(QPixmap(":/Images/Images/Player_Straight14.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                                break;
                            case 8:setPixmap(QPixmap(":/Images/Images/Player_Straight15.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                                break;
                            case 9:setPixmap(QPixmap(":/Images/Images/Player_Straight16.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                                break;
                            case 10:setPixmap(QPixmap(":/Images/Images/Player_Straight17.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                                break;
                            case 11:setPixmap(QPixmap(":/Images/Images/Player_Straight18.png").scaled(QPixmap(":/Images/Images/Player_Turn_Right11.png").width()* scaling, QPixmap(":/Images/Images/Player_Turn_Right11.png").height()* scaling));
                                movedDown = 0;
                                break;
                        }
                    }
                }
                hasMovedDown = true;
            }

        if(k == shoot){
            equippedWeapon->softSetCanFire(true);
        }
    }
}

//Slow actions, actions we don't want to instantly and immediately respond to player input, occur every second
void Player::keyPressSlowAction()
{

    collision = collidingItems();
    //traverse set
    foreach(QGraphicsItem* c, collision) {
        if(typeid(*(c)) == typeid(enemyOne) || typeid(*(c)) == typeid(enemyTwo) || typeid(*(c)) == typeid(enemyThree) || typeid(*(c)) == typeid(enemyFour)) {
           decrementHealth();
           return;
        }
    }
}
