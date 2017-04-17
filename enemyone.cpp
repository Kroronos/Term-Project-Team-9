#include "enemyone.h"
#include <QtCore>
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>

//moved in a straight line down the screen
enemyOne::enemyOne(double scaling, double speed)
    :Enemy(":/Images/Images/Enemy_1.png",scaling/3.5)
{
        this->speed = speed;
        myEnemyWeapon = new Weapon();
        // set random Position
        int random_number = rand() % 1300;
        setPos(random_number,0);

        // Connect
        timer = new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(move()));

        timer->start(25);
}

void enemyOne::move()
{
    // Move Enemy down
    setPos(x(),y()+speed + 2+speed);
    if(pos().y() > scene()->height()){
        scene()->removeItem(this);
        delete this->myEnemyWeapon;
        delete this;
        return;
    }
}
