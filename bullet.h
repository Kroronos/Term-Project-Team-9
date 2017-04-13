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
    //Create normal circular bullet
    Bullet(bool playerMade, double x, double y, double size, double scaling);

    //Create rectangular bullet, for lasers
    Bullet(bool playerMade, double width, double height, double scaling);

    bool getPlayerMade();

public slots:
    void move();
};

#endif // BULLET_H
