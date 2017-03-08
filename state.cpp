#include "state.h"
#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsView>


State::State()
{
sScene = new QGraphicsScene();
sView = new QGraphicsView();
}

void State::setSceneInView()
{
    sView->setScene(sScene);
}

void State::showView()
{
    sView->show();
}
