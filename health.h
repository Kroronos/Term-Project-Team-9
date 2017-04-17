#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>

class Health: public QGraphicsTextItem{
public:
    QGraphicsTextItem * text;
    Health(QGraphicsItem * parent=0);
    void increase();
    void decrease();
    void resetHealth();
    int getHealth();
private:
    int health;
};

#endif // HEALTH_H
