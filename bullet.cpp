#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include "enemyone.h"
#include "enemytwo.h"
#include "enemythree.h"
#include "enemyfour.h"
#include "actor.h"
#include "score.h"
#include "gameloop.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDebug>

// has access to global variable global game, for collision operations
extern gameLoop * globalGame;

Bullet::Bullet(bool playerMade, double x, double y, double scaling)
    :Actor(":/Images/Images/Bullet.png", scaling)
{
    globalGame->Bullets.push_back(this);
    movementTimer = new QTimer();
    connect(movementTimer,SIGNAL(timeout()), this, SLOT(move()));
    this->playerMade = playerMade;
    xMove = x * getScaling();
    yMove = y * getScaling();

    movementTimer->start(50);

}

Bullet::Bullet(bool upsideDown, bool playerMade, double x, double y, double scaling)
    :Actor(":/Images/Images/Bullet_Enemy.png", scaling)
{
    globalGame->Bullets.push_back(this);
    movementTimer = new QTimer();
    connect(movementTimer,SIGNAL(timeout()), this, SLOT(move()));
    this->playerMade = playerMade;
    xMove = x * getScaling();
    yMove = y * getScaling();

    movementTimer->start(50);
}

Bullet::~Bullet()
{
    delete movementTimer;
}

void Bullet::move()
{
    //set containing all collisions
    collision = collidingItems();
    //traverse set
    foreach(QGraphicsItem* c, collision) {
        if(playerMade) {
            //check to see if enemy is hit by player bullet
            if(typeid(*(c)) == typeid(enemyOne) || typeid(*(c)) == typeid(enemyTwo) || typeid(*(c)) == typeid(enemyThree) || typeid(*(c)) == typeid(enemyFour)) {
                scene()->removeItem(this);

                globalGame->deleteEnemy(c);
                if(globalGame->score){
                    globalGame->score->increase();
                }
                else {
                    globalGame->score = new Score();
                    globalGame->scene->removeItem(globalGame->score->scoreBoard);
                    globalGame->score->increase();
                }
                delete this;
                return;
            }
        }
        else {
            //check to see if player is hit by enemy bullet
            if(typeid(*c) == typeid(Player)) {

                globalGame->player->decrementHealth();
                scene()-> removeItem(this);
                delete this;
                return;
            }
        }
    }


    //Move away from player
    if(playerMade){
        setPos(x()+xMove,y()-yMove);

        //Delete bullets when they leave upper region
        if(pos().y() < 0- 2*getHeight()){
            scene()->removeItem(this);
            delete this;
        }
    }
    //Move towards player
    else {

       setPos(x()+xMove,y()+yMove);
       //Delete bullets when they leave bottom region
       if(pos().y() > scene()->height() + 2*getHeight()){
           scene()->removeItem(this);
           delete this;
       }
    }
}
bool Bullet::getPlayerMade()
{
    return playerMade;
}

void Bullet::stopMovement()
{
    movementTimer->stop();
}

void Bullet::startMovement()
{
    movementTimer->start();
}
