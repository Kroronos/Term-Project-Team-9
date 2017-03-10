#include "weapon.h"
#include "player.h"
#include "bullet.h"
#include <QtCore>
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsView>

Weapon::Weapon(int rate,Player* owner)
{
    canSpread = false;
    canFire = false;
    this->owner = owner;
    //Initialize timer
    fireRate = new QTimer();

    //Connect timer to respective slots
    connect(fireRate,SIGNAL(timeout()), this, SLOT(shoot()));

    //Set interval based on rate
    fireRate-> start(rate);
}

Weapon::Weapon(int rate, Player *owner, int pellets)
{
    canSpread = true;
    canFire = false;
    numberOfPellets = pellets;
    this->owner = owner;
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
}

void Weapon::shoot()
{
    if(canFire && !canSpread) {
        Bullet* playerBullet = new Bullet(true, 0, 10);
        //hard-coded set pos, make dynamic based on player size
        owner->scene()->addItem(playerBullet);
        playerBullet->setPos(owner->x(),owner->y()-owner->getHeight());

    }
    if(canFire && canSpread) {
        //Even Number Of Pellets
        int middle = numberOfPellets/2;
        if(numberOfPellets % 2 == 0) {
            for(int i = 1; i <= middle; ++i) {
                int xDirection = ceil(5/(i));

                //x-Direction function of number of pellet
                //Spreading weapons are faster than normal
                Bullet* playerBullet = new Bullet(true, xDirection, 20);
                Bullet* playerBulletComp = new Bullet(true, -xDirection, 20);

                owner->scene()->addItem(playerBullet);
                owner->scene()->addItem(playerBulletComp);
                playerBullet->setPos(owner->x(),owner->y()-owner->getHeight());
                playerBulletComp->setPos(owner->x(),owner->y()-owner->getHeight());

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
                    Bullet* playerBullet = new Bullet(true, xDirection, 20);
                    Bullet* playerBulletComp = new Bullet(true, -xDirection, 20);

                    owner->scene()->addItem(playerBullet);
                    owner->scene()->addItem(playerBulletComp);
                    playerBullet->setPos(owner->x(),owner->y()-owner->getHeight());
                    playerBulletComp->setPos(owner->x(),owner->y()-owner->getHeight());
                }
                if (i == middle) {
                    //x-Direction function of number of pellet
                    //Spreading weapons are faster than normal
                    Bullet* playerBullet = new Bullet(true, 0, 20);

                    owner->scene()->addItem(playerBullet);
                    playerBullet->setPos(owner->x(),owner->y()-owner->getHeight());
                }

            }
        }
    }

}
