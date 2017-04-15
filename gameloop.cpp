#include "gameloop.h"
#include "state.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>

gameLoop::gameLoop(int x, int y)
    :State(x,y)
{
    qDebug() << QPixmap(":/Images/Images/Player_Straight5.png");
    //Create Player
    player = new Player(":/Images/Images/Player_Straight5.png",getScaling());

    //Add Player To Scene

    addItem(player);

    //Makes Player allowed to become focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    //Allows Player to receive input
    player->setFocus();

    setSceneInView();
    showView();


}
