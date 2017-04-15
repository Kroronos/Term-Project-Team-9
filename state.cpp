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
    if(x == 1920 && y == 1080) {
        sView->showFullScreen();
    }

    calculateScaling();
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

//Add any item to scene
void State::addItem(QGraphicsItem* item)
{
    sScene->addItem(item);
}

//Specific to add player to scene
void State::addItem(Player *player)
{
    sScene->addItem(player);
    //Center player in screen
    //TODO Make dynamic ie no hard coding pxl
    player->setPos(xDimension/2, yDimension - 1.1*(player->getHeight()));

}

void State::calculateScaling()
{
    //calculates by y-value
    scaling = double(yDimension)/1080;
}

double State::getScaling()
{
    return scaling;
}
