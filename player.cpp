#include "player.h"
#include "actor.h"
#include "QKeyEvent"
#include <QtCore>
#include <QObject>
#include <QTimer>
#include <QTimerEvent>

Player::Player(double vertexA, double vertexB, double vertexC)
    : Actor(vertexA, vertexB, vertexC)
{
    //Makes Player allowed to become focusable
    setFlag(QGraphicsItem::ItemIsFocusable);
    //Allows Player to receive input
    setFocus();

    //Initialize imer
    timer = new QTimer();
    //Connect timer to slot
    connect(timer,SIGNAL(timeout()), this, SLOT(keyPressAction()));
    //Set interval and start timer
    timer-> start(50);
}

//Adds Keys Pressed By Player To A Set
void Player::keyPressEvent(QKeyEvent* event)
{
    keysPressed += (Qt::Key)event->key();
}

//Removes Keys Released By Player from Set
void Player::keyReleaseEvent(QKeyEvent* event)
{
    keysPressed -= (Qt::Key)event->key();
}

//Acts on a timer interval for each key pressed
void Player::keyPressAction()
{
    foreach(Qt::Key k, keysPressed){
        //Move right
        if(k == Qt::Key_A) {
            setPos(x()-10, y());
        }
        //Move left
        if(k == Qt::Key_D) {
            setPos(x()+10, y());
        }
        //Move up
        if(k == Qt::Key_W) {
            setPos(x(), y()-10);
        }
        //Move down
        if(k == Qt::Key_S) {
            setPos(x(), y()+10);
        }
    }
}


