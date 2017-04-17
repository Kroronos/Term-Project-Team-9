#ifndef BULLET_H
#define BULLET_H
#include "actor.h"
#include <QObject>
#include <QtCore>
#include <QList>
#include <QTimer>

class Bullet : public Actor
{
    Q_OBJECT
private:
    QTimer* movementTimer;
    bool playerMade;
    double xMove;
    double yMove;

    //Stores collsions
    QList<QGraphicsItem *> collision;

public:
    //Create normal circular bullet
    Bullet(bool playerMade, double x, double y, double scaling);
    Bullet(bool upsideDown, bool playerMade, double x, double y, double scaling);

    bool getPlayerMade();
    void stopMovement();
    void startMovmement();

public slots:
    void move();
};

#endif // BULLET_H
