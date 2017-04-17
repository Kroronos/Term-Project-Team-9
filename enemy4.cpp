#include "enemy4.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> Really Large Int


Enemy4::Enemy4(): QObject(), QGraphicsRectItem(){
    // set random Position
    int random_number = rand() % 1300;
    int random_distance = rand()% 100;
    setPos(random_number,random_distance);

    // Drew the rect
    setRect(0,0,50,50);

    // Connect
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(25);
}


int count4 = 0;
bool sidetoside = false;
bool direction;
int random_distance = rand()% 400;

void Enemy4::move()
{

    if(count4 <= random_distance){      // Initiate falling
          setPos(x(),y() + 2);
          count4++;

                   if (count4 == random_distance){
                       sidetoside = true;
               }

     }

    if(sidetoside == true){ //Switching to sidetoside AI
        if (pos().x() >= 1300){
            direction = false;
        } else if(pos().x() <= 60){
             direction = true;
        }
        if(direction == false){
             setPos(x()-2,y());
        }
        if(direction == true){
             setPos(x()+2,y());
        }

    }


    if(pos().y() + rect().height() > 800){
        scene()->removeItem(this);
        delete this;
    }
}
