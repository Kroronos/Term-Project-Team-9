#include "gameloop.h"
#include "state.h"

gameLoop::gameLoop(int x, int y)
    :State(x,y)
{
    //Create Player
    player = new Player(-15, -85, 15,getScaling());

    //Add Player To Scene
    addItem(player);

    //Makes Player allowed to become focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    //Allows Player to receive input
    player->setFocus();

    setSceneInView();
    showView();

    //Everything after this belongs to you wesley
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
