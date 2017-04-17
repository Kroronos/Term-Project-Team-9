#ifndef ROUNDS_H
#define ROUNDS_H

#include <QGraphicsTextItem>
#include <QGraphicsItem>

class rounds: public QGraphicsTextItem{

public:
    QGraphicsTextItem * roundDisplay;
    rounds(QGraphicsItem * parent=0);
    void increase();
    int getRounds();
    int roundsCount = 0;


};

#endif // ROUNDS_H
