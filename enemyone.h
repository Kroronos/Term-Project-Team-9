#ifndef ENEMYONE_H
#define ENEMYONE_H
#include "enemy.h"
#include <QObject>

class enemyOne: public Enemy
{
    Q_OBJECT
public:
    enemyOne(double scaling);
public slots:
    void move();
};

#endif // ENEMYONE_H
