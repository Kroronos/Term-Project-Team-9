#include "health.h"
#include "gameloop.h"
#include <QFont>


// has access to global variable global game, to call game over screen
extern gameLoop * globalGame;
Health::Health(QGraphicsItem *parent) : QGraphicsTextItem(parent){
    //initialize health to 3
    health = 3;

    //draw text
    text = new QGraphicsTextItem();
    text->setPlainText(QString("Health: ") + QString::number(health)); //Health: 3
    text->setDefaultTextColor(Qt::red);
    text->setFont(QFont("times", 16));
}

void Health::increase()
{
    ++health;
    text->setPlainText(QString("Health: ") + QString::number(health));
    update();
}

void Health::decrease(){
   if(health >= 1)
   {
       --health;
        text->setPlainText(QString("Health: ") + QString::number(health)); //Health: 2
        update();
        //call game over screen
        if (health == 0)
        {
            globalGame->gameOver();
        }
   }
}

void Health::resetHealth(){
    health = 3;
}

int Health::getHealth(){
    return health;
}

