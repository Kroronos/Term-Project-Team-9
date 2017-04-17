#include "score.h"
#include <QFont>

Score::Score(QGraphicsItem * parent) : QGraphicsTextItem(parent){
    //intitialize the score to 0
    score = 0;
    scoreBoard = new QGraphicsTextItem();
    //draw the text
    scoreBoard->setPlainText(QString("Score: ") + QString::number (score)); //score: 0
    scoreBoard->setDefaultTextColor(Qt::blue);  //choose font color
    scoreBoard->setFont(QFont("times",16));  //choose font and size
}

void Score::increase(){
    score += 100;
    scoreBoard->setPlainText(QString("Score: ") + QString::number (score)); //score: 1

}

int Score::getScore(){
    return score;
}
