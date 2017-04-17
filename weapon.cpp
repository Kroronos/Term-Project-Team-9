#include "weapon.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include <QtCore>
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsView>

Weapon::Weapon()
{
    canFire = false;
    canSpread = false;
    owner = nullptr;
    ownerTwo = nullptr;
    fireRate = nullptr;
}

Weapon::Weapon(int rate,Player* owner,Enemy* ownerTwo, double scaling)
{
    this->scaling = scaling;
    canSpread = false;
    canFire = false;
    //set owners
    this->owner = owner;
    this->ownerTwo = ownerTwo;
    //Initialize timer
    fireRate = new QTimer();

    //Connect timer to respective slots
    connect(fireRate,SIGNAL(timeout()), this, SLOT(shoot()));

    //Set interval based on rate
    fireRate-> start(rate);
}

Weapon::Weapon(int rate, Player *owner, Enemy* ownerTwo, int pellets, double scaling)
{
    this->scaling = scaling;
    canSpread = true;
    canFire = false;
    numberOfPellets = pellets;
    //set owners
    this->owner = owner;
    this->ownerTwo = ownerTwo;
    //Initialize timer
    fireRate = new QTimer();

    //Connect timer to respective slots
    connect(fireRate,SIGNAL(timeout()), this, SLOT(shoot()));

    //Set interval based on rate
    fireRate-> start(rate);
}

bool Weapon::getCanFire()
{
    return canFire;
}

void Weapon::setCanFire(bool a)
{
    canFire = a;
    //Stops timer to prevent weapon being stuck in infinite shooting loop during pause, also reduces redundant calls when falser
    if(a) {
        if(fireRate) {
            fireRate->start();
        }
    }
    else {
        if(fireRate) {
            fireRate->stop();
        }
    }
}

void Weapon::softSetCanFire(bool a)
{
    canFire = a;
}

void Weapon::shoot()
{
    if(owner) {
        if(canFire && !canSpread) {
            Bullet* playerBullet;

            playerBullet = new Bullet(true, 0, 10, scaling);
            owner->scene()->addItem(playerBullet);
            playerBullet->setPos(owner->x() + owner->getWidth()/4,owner->y()-owner->getHeight()/8 - owner->getHeight()/8);
        }


        if(canFire && canSpread) {
            //Even Number Of Pellets
            int middle = numberOfPellets/2;
            if(numberOfPellets % 2 == 0) {
                for(int i = 1; i <= middle; ++i) {
                    int xDirection = ceil(5/(i));

                    //x-Direction function of number of pellet
                    //Spreading weapons are faster than normal
                    Bullet* playerBullet = new Bullet(true, xDirection, 20, scaling);
                    Bullet* playerBulletComp = new Bullet(true, -xDirection, 20, scaling);

                    owner->scene()->addItem(playerBullet);
                    owner->scene()->addItem(playerBulletComp);
                    playerBullet->setPos(owner->x()+ owner->getWidth()/4,owner->y()-owner->getHeight()/8 - owner->getHeight()/8);
                    playerBulletComp->setPos(owner->x()+ owner->getWidth()/4,owner->y()-owner->getHeight()/8 - owner->getHeight()/8);

                }
            }
            //Odd Number Of Pellets
            else {
                int middle = ceil(numberOfPellets/2)+1;
                for(int i = 1; i <= middle; ++i) {
                    int xDirection = ceil(5/(i));
                    if(i < middle) {
                        //x-Direction function of number of pellet
                        //Spreading weapons are faster than normal
                        Bullet* playerBullet = new Bullet(true, xDirection, 20, scaling);
                        Bullet* playerBulletComp = new Bullet(true, -xDirection, 20, scaling);

                        owner->scene()->addItem(playerBullet);
                        owner->scene()->addItem(playerBulletComp);
                        playerBullet->setPos(owner->x() - playerBullet->getWidth()/12,owner->y()-owner->getHeight()/8 - owner->getHeight()/8);
                        playerBulletComp->setPos(owner->x() - playerBullet->getWidth()/12,owner->y()-owner->getHeight()/8 - owner->getHeight()/8);
                    }
                    if (i == middle) {
                        //x-Direction function of number of pellet
                        //Spreading weapons are faster than normal
                        Bullet* playerBullet = new Bullet(true, 0, 20, scaling);

                        owner->scene()->addItem(playerBullet);
                        playerBullet->setPos(owner->x() - playerBullet->getWidth()/12,owner->y()-owner->getHeight()/3);
                    }

                }
            }
        }

    }

    //Weapon owned by enemy
    if(ownerTwo) {
        canFire = true;
        if(canFire && !canSpread) {
            Bullet* enemyBullet;

            enemyBullet = new Bullet(true,false, 0, 10, scaling);
            ownerTwo->scene()->addItem(enemyBullet);
            enemyBullet->setPos(ownerTwo->x()+ ownerTwo->getWidth()/3.75,ownerTwo->y()+ownerTwo->getHeight()/1.75);
        }


        if(canFire && canSpread) {
            //Even Number Of Pellets
            int middle = numberOfPellets/2;
            if(numberOfPellets % 2 == 0) {
                for(int i = 1; i <= middle; ++i) {
                    int xDirection = ceil(5/(i));

                    //x-Direction function of number of pellet
                    //Spreading weapons are faster than normal
                    Bullet* enemyBullet = new Bullet(true,false, xDirection, 20, scaling);
                    Bullet* enemyBulletComp = new Bullet(true,false, -xDirection, 20, scaling);

                    ownerTwo->scene()->addItem(enemyBullet);
                    ownerTwo->scene()->addItem(enemyBulletComp);
                    enemyBullet->setPos(ownerTwo->x()+ ownerTwo->getWidth()/3.75,ownerTwo->y()+ownerTwo->getHeight()/1.75);
                    enemyBulletComp->setPos(ownerTwo->x()+ ownerTwo->getWidth()/3.75,ownerTwo->y()+ownerTwo->getHeight()/1.75);

                }
            }
            //Odd Number Of Pellets
            else {
                int middle = ceil(numberOfPellets/2)+1;
                for(int i = 1; i <= middle; ++i) {
                    int xDirection = ceil(5/(i));
                    if(i < middle) {
                        //x-Direction function of number of pellet
                        //Spreading weapons are faster than normal
                        Bullet* enemyBullet = new Bullet(true,false, xDirection, 20, scaling);
                        Bullet* enemyBulletComp = new Bullet(true,false, -xDirection, 20, scaling);

                        ownerTwo->scene()->addItem(enemyBullet);
                        ownerTwo->scene()->addItem(enemyBulletComp);
                        enemyBullet->setPos(ownerTwo->x()+ ownerTwo->getWidth()/3.75,ownerTwo->y()+ownerTwo->getHeight()/1.75);
                        enemyBulletComp->setPos(ownerTwo->x()+ ownerTwo->getWidth()/3.75,ownerTwo->y()+ownerTwo->getHeight()/1.75);
                    }
                    if (i == middle) {
                        //x-Direction function of number of pellet
                        //Spreading weapons are faster than normal
                        Bullet* enemyBullet = new Bullet(true,false, 0, 20, scaling);

                        ownerTwo->scene()->addItem(enemyBullet);
                        enemyBullet->setPos(ownerTwo->x()+ ownerTwo->getWidth()/3.75,ownerTwo->y()+ownerTwo->getHeight()/1.75);
                    }

                }
            }
        }

    }

}
