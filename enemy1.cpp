#include "enemy1.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> Really Large Int


Enemy1::Enemy1(): QObject(), QGraphicsRectItem(){
    // set random Position
    int random_number = rand() % 1300;
    setPos(random_number,0);

    // Drew the rect
    setRect(0,0,50,50);

    // Connect
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(25);
}



void Enemy1::move()
{
    // Move Enemy down
    setPos(x(),y() + 2);
    if(pos().y() + rect().height() > 800){
        scene()->removeItem(this);
        delete this;
    }
}
