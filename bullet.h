#ifndef BULLET_H
#define BULLET_H
#include "actor.h"
#include <QtCore>
#include <QObject>
#include <QList>
#include <QTimer>

class Bullet : /*public QObject,*/ public Actor
{
    Q_OBJECT
private:
    QTimer* movementTimer;
    bool playerMade;
    double xMove;
    double yMove;

    //Stores bullet collsions
    QList<QGraphicsItem *> collision;

public:
    //Create normal circular bullet
    Bullet(bool playerMade, double x, double y, double scaling);

    bool getPlayerMade();

public slots:
    void move();
};

#endif // BULLET_H
