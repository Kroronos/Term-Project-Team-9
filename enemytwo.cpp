#include "enemytwo.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>

//moves in a zigzag pattern down screen
enemyTwo::enemyTwo(double scaling, double speed)
    :Enemy(":/Images/Images/Enemy_2.png", scaling/3.5)
{
       this->speed = speed;
       myEnemyWeapon = new Weapon(750, nullptr, this, scaling);
       // set random Position
       int random_number = rand() % 1300;
       setPos(random_number,0);

       // Connect
       timer = new QTimer(this);
       connect(timer,SIGNAL(timeout()),this,SLOT(move()));

       timer->start(25);
}

int count = 0;
void enemyTwo::move()
{
    // Move Enemy in a ZigZag
      if(count < 200){
      setPos(x()-speed+2+speed,y()+speed + 2+speed);
      count++;
      }
      if(count >=200){
      setPos(x()-speed-2+speed,y()+speed + 2+speed);
      count++;
      if (count == 400){
          count = 0;
      }
      }

      if(pos().y() > scene()->height()){
          scene()->removeItem(this);
          delete this;
          return;
      }
}
