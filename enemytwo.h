#ifndef ENEMYTWO_H
#define ENEMYTWO_H
#include "enemy.h"
#include <QObject>

class enemyTwo: public Enemy
{
    Q_OBJECT
public:
    enemyTwo(double scaling);
public slots:
    void move();
};

#endif // ENEMYTWO_H
