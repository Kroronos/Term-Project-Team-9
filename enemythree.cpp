#include "enemythree.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>

enemyThree::enemyThree(double scaling)
    :Enemy(":/Images/Images/Enemy_7.png", scaling/2)
{
      myEnemyWeapon = new Weapon(1000, nullptr, this, scaling);
      // set random Position
      int random_number = rand() % 1300;
      setPos(random_number,0);

      // Connect
      timer = new QTimer(this);
      connect(timer,SIGNAL(timeout()),this,SLOT(move()));

      timer->start(50);
}

int count2 = 0;
void enemyThree::move()
{

    //Delete of boundaries
    if(pos().y() > scene()->height()){
        scene()->removeItem(this);
        delete this->myEnemyWeapon;
        delete this;
        return;
    }

    // Move Enemy in a Circle
    switch(count2){
    case 0:     setPos(x(),y() + 15);   count2++;    break;
    case 1:     setPos(x(),y() + 15);   count2++;    break;
    case 2:     setPos(x(),y() + 15);   count2++;    break;
    case 3:     setPos(x(),y() + 15);   count2++;    break;
    case 4:     setPos(x(),y() + 15);   count2++;    break;
    case 5:     setPos(x(),y() + 15);   count2++;    break;
    case 6:     setPos(x(),y() + 15);   count2++;    break;
    case 7:     setPos(x(),y() + 15);   count2++;    break;
    case 8:     setPos(x(),y() + 15);   count2++;    break;
    case 9:     setPos(x(),y() + 15);   count2++;    break;
    case 10:    setPos(x() + 15 ,y());   count2++;    break;
    case 11:    setPos(x() + 15 ,y());   count2++;    break;
    case 12:    setPos(x() + 15 ,y());   count2++;    break;
    case 13:    setPos(x() + 15 ,y());   count2++;    break;
    case 14:    setPos(x() + 15 ,y());   count2++;    break;
    case 15:    setPos(x() + 15 ,y());   count2++;    break;
    case 16:    setPos(x() + 15, y() + 15);   count2++;    break;
    case 17:    setPos(x() + 15, y() + 15);   count2++;    break;
    case 18:    setPos(x() + 15, y() + 15);   count2++;    break;
    case 19:    setPos(x() + 15, y() + 15);   count2++;    break;
    case 20:    setPos(x() + 15, y() + 15);   count2++;    break;
    case 21:    setPos(x() + 15, y() + 15);   count2++;    break;
    case 22:    setPos(x(), y() + 15);   count2++;    break;
    case 23:    setPos(x(), y() + 15);   count2++;    break;
    case 24:    setPos(x(), y() + 15);   count2++;    break;
    case 25:    setPos(x(), y() + 15);   count2++;    break;
    case 26:    setPos(x(), y() + 15);   count2++;    break;
    case 27:    setPos(x(), y() + 15);   count2++;    break;
    case 28:    setPos(x() - 15, y() + 15);   count2++;    break;
    case 29:    setPos(x() - 15, y() + 15);   count2++;    break;
    case 30:    setPos(x() - 15, y() + 15);   count2++;    break;
    case 31:    setPos(x() - 15, y() + 15);   count2++;    break;
    case 32:    setPos(x() - 15, y() + 15);   count2++;    break;
    case 33:    setPos(x() - 15, y() + 15);   count2++;    break;
    case 34:    setPos(x() - 15, y());   count2++;    break;
    case 35:    setPos(x() - 15, y());   count2++;    break;
    case 36:    setPos(x() - 15, y());   count2++;    break;
    case 37:    setPos(x() - 15, y());   count2++;    break;
    case 38:    setPos(x() - 15, y());   count2++;    break;
    case 39:    setPos(x() - 15, y());   count2++;    break;
    case 40:    setPos(x() - 15, y() - 15);   count2++;    break;
    case 41:    setPos(x() - 15, y() - 15);   count2++;    break;
    case 42:    setPos(x() - 15, y() - 15);   count2++;    break;
    case 43:    setPos(x() - 15, y() - 15);   count2++;    break;
    case 44:    setPos(x() - 15, y() - 15);   count2++;    break;
    case 45:    setPos(x() - 15, y() - 15);   count2++;    break;
    case 46:    setPos(x(), y() - 15);   count2++;    break;
    case 47:    setPos(x(), y() - 15);   count2++;    break;
    case 48:    setPos(x(), y() - 15);   count2++;    break;
    case 49:    setPos(x(), y() - 15);   count2++;    break;
    case 50:    setPos(x(), y() - 15);   count2++;    break;
    case 51:    setPos(x(), y() - 15);   count2++;    break;
    case 52:    setPos(x() + 15, y() - 15);   count2++;    break;
    case 53:    setPos(x() + 15, y() - 15);   count2++;    break;
    case 54:    setPos(x() + 15, y() - 15);   count2++;    break;
    case 55:    setPos(x() + 15, y() - 15);   count2++;    break;
    case 56:    setPos(x() + 15, y() - 15);   count2++;    break;
    case 57:    setPos(x() + 15, y() - 15);   count2++;    break;
    case 58:    setPos(x(),y() + 15);   count2++;    break;
    case 59:    setPos(x(),y() + 15);   count2++;    break;
    case 60:    setPos(x(),y() + 15);   count2++;    break;
    case 61:    setPos(x(),y() + 15);   count2++;    break;
    case 62:    setPos(x(),y() + 15);   count2++;    break;
    case 63:    setPos(x(),y() + 15);   count2++;    break;
    case 64:    setPos(x(),y() + 15);   count2++;    break;
    case 65:    setPos(x(),y() + 15);   count2++;    break;
    case 66:    setPos(x(),y() + 15);   count2++;    break;
    case 67:    setPos(x(),y() + 15);   count2++;    break;
    case 68:    setPos(x(),y() + 15);   count2++;    break;
    case 69:    setPos(x(),y() + 15);   count2++;    break;
    case 70:    setPos(x(),y() + 15);  count2 = 0;  break;
    }
}
