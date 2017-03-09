#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QGraphicsView>
#include <QtCore>
#include "state.h"
#include "actor.h"
#include "player.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    State* testingEnviron = new State(800,600);

    //Create Player
    Player* player = new Player(-10,-10,10);

    //Add Player To Scene
    testingEnviron->addItem(player);

    //Makes Player allowed to become focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    //Allows Player to receive input
    player->setFocus();

    testingEnviron->setSceneInView();
    testingEnviron->showView();

    return a.exec();
}
