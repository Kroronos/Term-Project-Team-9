#include "enemyfour.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>

//stays in upper portion of screen and shoots wile moving back and forth
enemyFour::enemyFour(double scaling, double speed)
    :Enemy(":/Images/Images/Enemy_4.png", scaling/3.5)
{
      count4 = 0;
      this->speed = speed;
      myEnemyWeapon = new Weapon(2500, nullptr, this, 3, scaling);
      // set random Position
      int random_number = rand() % 1300;
      int random_distance = rand()% 100;
      setPos(random_number,random_distance-175);
      // Connect
      timer = new QTimer(this);
      connect(timer,SIGNAL(timeout()),this,SLOT(move()));

      timer->start(25);
}


bool sidetoside = false;
bool direction;


void enemyFour::move()
{
    if(count4 == 0) {
        random_distance = (rand()% 300);
    }
    if(count4 <= random_distance){
    // Initiate falling
          setPos(x(),y()+3);
          count4++;
        if (count4 == random_distance){
            sidetoside = true;
        }

     }

    if(sidetoside == true){
        //Switching to sidetoside AI
        if (pos().x() >= 1300){
            direction = false;
        } else if(pos().x() <= 60){
             direction = true;
        }
        if(direction == false){
             setPos(x()-speed-2-speed,y());
        }
        if(direction == true){
             setPos(x()+speed+2,y());
        }

    }


    if(pos().y() + getHeight() > 2000){
        scene()->removeItem(this);
        delete this->myEnemyWeapon;
        delete this;
        return;
    }
}
