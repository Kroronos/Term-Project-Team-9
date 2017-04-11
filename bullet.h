#ifndef BULLET_H
#define BULLET_H
#include "actor.h"
#include <QtCore>
#include <QObject>
#include <QTimer>

class Bullet : public QObject, public Actor
{
    Q_OBJECT
private:
    QTimer* movementTimer;
    bool playerMade;
    double xMove;
    double yMove;
public:
    Bullet(bool playerMade, double xMove, double yMove);
    Bullet(bool playerMade, double x, double y, double distortion);

public slots:
    void move();
};

#endif // BULLET_H
