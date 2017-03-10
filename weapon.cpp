#include "weapon.h"
#include "player.h"
#include "bullet.h"
#include <QtCore>
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsView>

Weapon::Weapon(int rate, Player* owner)
{
    canFire = false;
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
    if(canFire) {
        Bullet* playerBullet = new Bullet(true, 0, 10);
        //hard-coded set pos, make dynamic based on player size
        owner->scene()->addItem(playerBullet);
        playerBullet->setPos(owner->x(),owner->y()-owner->getHeight());

    }

}
