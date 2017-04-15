#include "health.h"
#include <QFont>

Health::Health(QGraphicsItem *parent) : QGraphicsTextItem(parent){
    //initialize health to 3
    health = 3;

    //draw text
    setPlainText(QString("Health: ") + QString::number(health)); //Health: 3
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 16));
}

void Health::decrease(){
    health--;
    setPlainText(QString("Health: ") + QString::number(health)); //Health: 2
//    if (health == 0){   //check if this works properly
//        gameOver();
//    }
}

void Health::resetHealth(){
    health = 3;
}

int Health::getHealth(){
    return health;
}



