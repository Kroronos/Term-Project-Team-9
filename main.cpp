#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QGraphicsView>
#include <QtCore>
#include "state.h"
#include "actor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    State* testingEnviron = new State();

    //create poly and add into scene
    Actor* player = new Actor(-10,-10,10);
    // Add the triangle polygon to the scene
    testingEnviron->sScene->addItem(player->pTriangleItem);

    testingEnviron->setSceneInView();
    testingEnviron->showView();

    return a.exec();
}
