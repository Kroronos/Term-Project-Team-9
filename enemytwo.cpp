#include "enemytwo.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>

enemyTwo::enemyTwo(double scaling)
    :Enemy(":/Images/Images/Enemy_2.png", scaling/3.5)
{
       myEnemyWeapon = new Weapon();
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

      if(pos().y() > scene()->height()){
          scene()->removeItem(this);
          delete this->myEnemyWeapon;
          delete this;
          return;
      }
}
