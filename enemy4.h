#ifndef ENEMY4_H
#define ENEMY4_H

#include <QGraphicsRectItem>
#include <QObject>

class Enemy4: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
   Enemy4();
public slots:
    void move();
};


#endif // ENEMY4_H
