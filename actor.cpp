#include "actor.h"
#include <cmath>
#include <QtCore>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDebug>


Actor::Actor(const QString &fileName, double scaling)
    :QObject(), QGraphicsPixmapItem(QPixmap(fileName))
{
    boundingRectRef = boundingRect();
    this->scaling = scaling;
}

double Actor::getHeight()
{
    return boundingRectRef.height();
}

double Actor::getWidth()
{
    return boundingRectRef.width();
}

double Actor::getScaling()
{
    return scaling;
}
