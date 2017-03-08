#ifndef PLAYER_H
#define PLAYER_H
#include <QtCore>
#include <QObject>
#include <QTimer>
#include <QTimerEvent>
#include "actor.h"

class Player : public QObject,public Actor
{
    Q_OBJECT
private:
    QSet<Qt::Key> keysPressed;
    QTimer* timer;

public:
    Player(double vertexA, double vertexB, double vertexC);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

public slots:
    void keyPressAction();
};

#endif // PLAYER_H
