#ifndef ENEMYONE_H
#define ENEMYONE_H
#include "enemy.h"
#include <QObject>

class enemyOne: public Enemy
{
    Q_OBJECT
private:
    double speed;
public:
    enemyOne(double scaling, double speed);
public slots:
    void move();
};

#endif // ENEMYONE_H
