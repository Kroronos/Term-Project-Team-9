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
};

#endif // ENEMY_H
