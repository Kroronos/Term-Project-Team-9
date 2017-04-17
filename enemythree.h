#ifndef ENEMYTHREE_H
#define ENEMYTHREE_H
#include "enemy.h"
#include <QObject>

class enemyThree: public Enemy
{
    Q_OBJECT
private:
    double speed;
public:
    enemyThree(double scaling, double speed);
public slots:
    void move();
};

#endif // ENEMYTHREE_H
