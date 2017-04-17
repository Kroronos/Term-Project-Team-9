#ifndef ENEMY_H
#define ENEMY_H
#include <QObject>
#include "weapon.h"
#include "actor.h"

class Enemy : public Actor
{
public:
    Enemy(const QString &fileName, double scaling);
    //Used to shoot (not deleting this before deleting the enemy will cause nullptr exception, you have been warned)
    Weapon* myEnemyWeapon;
    QTimer * timer;

    //used to pause enemies in scene when pause is called
    //stops the weapon from shooting
    void stopShooting();
    //stops enemy from moving
    void stopMoving();
    //restarts shooting
    void startsShooting();
    //restarts moving
    void startsMoving();
};

#endif // ENEMY_H
