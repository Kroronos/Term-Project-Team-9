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

    State* testingEnviron = new State();

    //create poly and add into scene
    Player* player = new Player(-10,-10,10);
    // Add the triangle polygon to the scene
    testingEnviron->sScene->addItem(player);

    //Makes Player allowed to become focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    //Allows Player to receive input
    player->setFocus();

    testingEnviron->setSceneInView();
    testingEnviron->showView();

    return a.exec();
}
