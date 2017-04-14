#include "gameloop.h"

#include <QTimer>
#include <QList>
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsItem>
#include <stdlib.h>

gameLoop::gameLoop()
{
    int random_pos = rand() % 700;
    setPos(random_pos, 0);

    QTimer * roundtimer = new QTimer();
    QTimer * enemytimer = new QTimer();

    QObject::connect(enemytimer, SIGNAL(timeout()), /*enemy (DEFINE)*/ SLOT(/*spawn() (DEFINE)*/));
    if (roundtimer->timeout()){
        roundcount++;
        gameLoop();
    }

}
