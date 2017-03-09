#include "state.h"
#include "player.h"
#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsView>


State::State(int x, int y)
{
    sScene = new QGraphicsScene();
    sView = new QGraphicsView();

    xDimension=x;
    yDimension=y;
}

void State::setSceneInView()
{
    sView->setScene(sScene);
    //Set ScrollBar off to stop scroll bars from appearing when objects leave screen region
    sView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    sView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void State::showView()
{
    sView->show();

    //Show Scene and View In Equal Certain Pixel Dimensions
    sScene->setSceneRect(0,0,xDimension,yDimension);
    sView->setFixedSize(xDimension, yDimension);
}

void State::addItem(QGraphicsItem* item)
{
    sScene->addItem(item);
}

void State::addItem(Player *player)
{
    sScene->addItem(player);
    //Center player in screen
    //TODO Make dynamic ie no hard coding pxl
    player->setPos(sView->width()/2 +90, sView->height()+100);

}
