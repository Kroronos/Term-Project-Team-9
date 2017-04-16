#include "enemy2.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> Really Large Int


Enemy2::Enemy2(): QObject(), QGraphicsEllipseItem(){
    // set random Position
    int random_number = rand() % 1300;
    setPos(random_number,0);

    // Drew the Ellipse
    setRect(0,0,50,50);

    // Connect
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(25);
}


int count = 0;
void Enemy2::move()
{
    // Move Enemy in a ZigZag
    if(count < 200){
    setPos(x()+2,y() + 2);
    count++;
    }
    if(count >=200){
    setPos(x()-2,y() + 2);
    count++;
    if (count == 400){
        count = 0;
    }
    }

    if(pos().y() + rect().height() > 800){
        scene()->removeItem(this);
        delete this;
    }
}
