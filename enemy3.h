#ifndef ENEMY3_H
#define ENEMY3_H

#include <QGraphicsRectItem>
#include <QObject>

class Enemy3: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
   Enemy3();
public slots:
    void move();
};

#endif // ENEMY3_H
