#include "score.h"
#include "gameloop.h"
#include <QFont>
#include <QDebug>

extern gameLoop* globalGame;

Score::Score(QGraphicsItem * parent) : QGraphicsTextItem(parent){
    //intitialize the score to 0
    score = 0;
    scoreBoard = new QGraphicsTextItem();
    //draw the text
    scoreBoard->setPlainText(QString("Score: ") + QString::number (score)); //score: 0
    scoreBoard->setDefaultTextColor(Qt::blue);  //choose font color
    scoreBoard->setFont(QFont("times",16));  //choose font and sized
    globalGame->scene->addItem(this->scoreBoard);
}

void Score::increase(){
    //globalGame->scene->removeItem(this->scoreBoard);
    score += 100;
    scoreBoard->setPlainText(QString("Score: ") + QString::number (score)); //score: 1
    globalGame->scene->addItem(this->scoreBoard);

}

int Score::getScore(){
    return score;
}
