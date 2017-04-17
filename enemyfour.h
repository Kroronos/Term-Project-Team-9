#ifndef ENEMYFOUR_H
#define ENEMYFOUR_H
#include "enemy.h"
#include <QObject>

class enemyFour: public Enemy
{
    Q_OBJECT
public:
    enemyFour(double scaling);
public slots:
    void move();
};

#endif // ENEMYFOUR_H
