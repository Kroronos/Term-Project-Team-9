#include "enemy.h"
#include "actor.h"


Enemy::Enemy(const QString &fileName, double scaling)
    :Actor(fileName, scaling)
{
}

void Enemy::stopShooting()
{

    if(myEnemyWeapon) {
        myEnemyWeapon->setCanFire(false);
    }
}

void Enemy::stopMoving()
{
    timer->stop();
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

