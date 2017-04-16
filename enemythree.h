#ifndef ENEMYTHREE_H
#define ENEMYTHREE_H
#include "enemy.h"
#include <QObject>

class enemyThree: public Enemy
{
    Q_OBJECT
public:
    enemyThree(double scaling);
public slots:
    void move();
};

#endif // ENEMYTHREE_H
