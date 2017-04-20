#include "enemy.h"
#include "actor.h"


Enemy::Enemy(const QString &fileName, double scaling)
    :Actor(fileName, scaling)
{
}

Enemy::~Enemy()
{
    if(myEnemyWeapon != nullptr) {
        delete myEnemyWeapon;
    }
    if(timer != nullptr) {
        delete timer;
    }
}

void Enemy::stopShooting()
{

    if(myEnemyWeapon) {
        myEnemyWeapon->setCanFire(false);
    }
}

void Enemy::stopMoving()
{
    if(this != nullptr) {
        if(timer != nullptr) {
            timer->stop();
        }
    }

}

void Enemy::startsShooting()
{
    if(myEnemyWeapon){
        myEnemyWeapon->setCanFire(true);
    }
}

void Enemy::startsMoving()
{
    timer->start();
}

