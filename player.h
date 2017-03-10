#ifndef PLAYER_H
#define PLAYER_H
#include <QtCore>
#include <QObject>
#include <QTimer>
#include <QTimerEvent>
#include "actor.h"
#include "weapon.h"

class Player : public QObject,public Actor
{
    Q_OBJECT
private:
    QSet<Qt::Key> keysPressed;
    //Timer used to update movement and similar actions that should happen on a very fast interval
    QTimer* fastTimer;
    //Timer used for staggered actions that should be continous
    QTimer* slowTimer;
    Weapon* equippedWeapon;

public:
    Player(double vertexA, double vertexB, double vertexC);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

public slots:
    void keyPressFastAction();
    void keyPressSlowAction();
};

#endif // PLAYER_H
