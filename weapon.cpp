#include "weapon.h"
#include "player.h"
#include "bullet.h"
#include <QtCore>
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsView>

Weapon::Weapon(int rate,Player* owner, double scaling)
{
    this->scaling = scaling;
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

Weapon::Weapon(int rate, Player *owner, int pellets, double scaling)
{
    this->scaling = scaling;
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
        Bullet* playerBullet;

        playerBullet = new Bullet(true, 0, 10, scaling);
        owner->scene()->addItem(playerBullet);
        playerBullet->setPos(owner->x() + owner->getWidth()/7,owner->y()-owner->getHeight()/8 - owner->getHeight()/4);
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
                playerBullet->setPos(owner->x()+ owner->getWidth()/7,owner->y()-owner->getHeight()/8 - owner->getHeight()/4);
                playerBulletComp->setPos(owner->x()+ owner->getWidth()/7,owner->y()-owner->getHeight()/8 - owner->getHeight()/4);

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
                    playerBullet->setPos(owner->x()+ owner->getWidth()/7,owner->y()-owner->getHeight()/8 - owner->getHeight()/4);
                    playerBulletComp->setPos(owner->x()+ owner->getWidth()/7,owner->y()-owner->getHeight()/8 - owner->getHeight()/4);
                }
                if (i == middle) {
                    //x-Direction function of number of pellet
                    //Spreading weapons are faster than normal
                    Bullet* playerBullet = new Bullet(true, 0, 20, scaling);

                    owner->scene()->addItem(playerBullet);
                    playerBullet->setPos(owner->x()+ owner->getWidth()/7,owner->y()-owner->getHeight()/8 - owner->getHeight()/4);
                }

            }
        }
    }

}
