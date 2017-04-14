#include "gameloop.h"
#include "state.h"
#include "enemy.h"

#include <QObject>
#include <QTimer>

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

    if(roundcount > 6){
        //code for the end of the game
    }
    else{
        //Everything after this belongs to you wesley
        QTimer * roundtimer = new QTimer();
        QTimer * enemytimer = new QTimer();

        QObject::connect(enemytimer,SIGNAL(timeout()), enemy, SLOT(spawn()));
        roundtimer->start(180000); //This sets the round timer to 3 minutes
        enemytimer->start(5000); //We can adjust this number for difficulty

        if (roundtimer->timeout()){
            roundcount++;
            gameloop();
        }
    }
}
