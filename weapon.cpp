#include "weapon.h"
#include "player.h"
#include "bullet.h"
#include <QtCore>
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsView>

Weapon::Weapon(int rate,Player* owner, double bulletSize, double scaling)
{
    this->scaling = scaling;
    this->bulletSize = bulletSize;
    isLaser = false;
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

Weapon::Weapon(int rate, Player *owner,double bulletSize, int pellets, double scaling)
{
    this->scaling = scaling;
    this->bulletSize = bulletSize;
    isLaser = false;
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

Weapon::Weapon(Player* owner, double bulletSize, double scaling) {
    this->scaling = scaling;
    this->bulletSize = bulletSize;
    isLaser = true;
    canSpread = false;
    canFire = false;
    this->owner = owner;
    //Initialize timer
    fireRate = new QTimer();

    //connect timer to respective slots
    connect(fireRate,SIGNAL(timeout()), this, SLOT(shoot()));

    //Set laser interval
    fireRate->start(50);
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
        Bullet* playerBullet;
        if(!isLaser) {
            playerBullet = new Bullet(true, 0, 10, bulletSize, scaling);
            owner->scene()->addItem(playerBullet);
            playerBullet->setPos(owner->x(),owner->y()-owner->getHeight());
        }
        if(isLaser) {
            playerBullet = new Bullet(true, bulletSize,1920 - owner->y(), scaling);
            owner->scene()->addItem(playerBullet);
            playerBullet->setPos(owner->x() - playerBullet->getWidth()/4,owner->y()-(owner->getHeight() + playerBullet->getHeight()));
        }


    }
    if(canFire && canSpread) {
        qDebug() << "AM I HERE?";
        //Even Number Of Pellets
        int middle = numberOfPellets/2;
        if(numberOfPellets % 2 == 0) {
            for(int i = 1; i <= middle; ++i) {
                int xDirection = ceil(5/(i));

                //x-Direction function of number of pellet
                //Spreading weapons are faster than normal
                Bullet* playerBullet = new Bullet(true, xDirection, 20, bulletSize, scaling);
                Bullet* playerBulletComp = new Bullet(true, -xDirection, 20, bulletSize, scaling);

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
                    Bullet* playerBullet = new Bullet(true, xDirection, 20, bulletSize, scaling);
                    Bullet* playerBulletComp = new Bullet(true, -xDirection, 20, bulletSize, scaling);

                    owner->scene()->addItem(playerBullet);
                    owner->scene()->addItem(playerBulletComp);
                    playerBullet->setPos(owner->x(),owner->y()-owner->getHeight());
                    playerBulletComp->setPos(owner->x(),owner->y()-owner->getHeight());
                }
                if (i == middle) {
                    //x-Direction function of number of pellet
                    //Spreading weapons are faster than normal
                    Bullet* playerBullet = new Bullet(true, 0, 20, bulletSize, scaling);

                    owner->scene()->addItem(playerBullet);
                    playerBullet->setPos(owner->x(),owner->y()-owner->getHeight());
                }

            }
        }
    }

}
