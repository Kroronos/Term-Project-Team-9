#ifndef ENEMY1_H
#define ENEMY1_H

#include <QGraphicsRectItem>
#include <QObject>

class Enemy1: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
   Enemy1();
public slots:
    void move();
};


#endif // ENEMY1_H
