#ifndef ENEMYFOUR_H
#define ENEMYFOUR_H
#include "enemy.h"
#include <QObject>

class enemyFour: public Enemy
{
    Q_OBJECT
private:
    double speed;
public:
    enemyFour(double scaling, double speed);
public slots:
    void move();
};

#endif // ENEMYFOUR_H
