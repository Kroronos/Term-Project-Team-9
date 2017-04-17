#include "rounds.h"
#include <QFont>

rounds::rounds(QGraphicsItem * parent) : QGraphicsTextItem(parent){
    //intitialize the score to 0
    roundsCount = 0;
    roundDisplay = new QGraphicsTextItem();
    //draw the text
    roundDisplay->setPlainText(QString("Round: ") + QString::number (roundsCount)); //score: 0
    roundDisplay->setDefaultTextColor(Qt::white);  //choose font color
    roundDisplay->setFont(QFont("times",40));  //choose font and size
    roundDisplay->setPos(800, 20);
}

void rounds::increase(){
    ++roundsCount;
    roundDisplay->setPlainText(QString("Score: ") + QString::number (roundsCount)); //score: 1

}

int rounds::getRounds(){
    return roundsCount;
}
