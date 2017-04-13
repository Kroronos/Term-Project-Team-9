#include <QApplication>
#include <QDebug>
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

    State* testingEnviron = new State(1920,1080);

    //Create Player
    Player* player = new Player(-15, -85, 15, testingEnviron->getScaling());

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
