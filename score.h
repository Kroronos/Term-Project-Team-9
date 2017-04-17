#ifndef SOURCE_H
#define SOURCE_H

#include <QGraphicsTextItem>



class Score: public QGraphicsTextItem{
public:
    QGraphicsTextItem * scoreBoard;
    Score (QGraphicsItem * parent=0);
    void increase();
    int getScore();

private:
    int score;
};

#endif // SOURCE_H
