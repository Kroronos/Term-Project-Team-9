#ifndef ENEMYTWO_H
#define ENEMYTWO_H
#include "enemy.h"
#include <QObject>

class enemyTwo: public Enemy
{
    Q_OBJECT
private:
    double speed;
public:
    enemyTwo(double scaling, double speed);
public slots:
    void move();
};

#endif // ENEMYTWO_H
