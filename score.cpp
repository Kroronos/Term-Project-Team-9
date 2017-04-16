#include "score.h"
#include <QFont>

Score::Score(QGraphicsItem * parent) : QGraphicsTextItem(parent){
    //intitialize the score to 0
    score = 0;

    //draw the text
    setPlainText(QString("Score: ") + QString::number (score)); //score: 0
    setDefaultTextColor(Qt::blue);  //choose font color
    setFont(QFont("times",16));  //choose font and size
}

void Score::increase(){
    score++;
    setPlainText(QString("Score: ") + QString::number (score)); //score: 1

}

int Score::getScore(){
    return score;
}
