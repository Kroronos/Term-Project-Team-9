#include "health.h"
#include "gameloop.h"
#include <QFont>


// has access to global variable global game, to call game over screen
extern gameLoop * globalGame;
Health::Health(QGraphicsItem *parent) : QGraphicsTextItem(parent){
    //initialize health to 3
    health = 3;

    //draw text
    setPlainText(QString("Health: ") + QString::number(health)); //Health: 3
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 16));
}

void Health::increase()
{
    ++health;
    setPlainText(QString("Health: ") + QString::number(health));
}

void Health::decrease(){
    --health;
    setPlainText(QString("Health: ") + QString::number(health)); //Health: 2
   if (health == 0){   //call game over screen
       globalGame->gameOver();
   }
}

void Health::resetHealth(){
    health = 3;
}

int Health::getHealth(){
    return health;
}

