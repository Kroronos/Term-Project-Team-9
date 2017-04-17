#ifndef ENEMY2_H
#define ENEMY2_H


#include <QGraphicsEllipseItem>
#include <QObject>

class Enemy2: public QObject, public QGraphicsEllipseItem{
    Q_OBJECT
public:
   Enemy2();
public slots:
    void move();
};

#endif // ENEMY2_H
