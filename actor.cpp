#include "actor.h"
#include <cmath>
#include <QtCore>
#include <QGraphicsPolygonItem>

//Triangle Constructor
Actor::Actor(double vertexA, double vertexB, double vertexC)
    : QGraphicsPolygonItem() {

    //Left Point
    this->vertexA = int(abs(vertexA));
    //Horizontal
    this->vertexB = int(abs(vertexB));
    //Right Point
    this->vertexC = int(abs(vertexC));

    //Vertex A is negative
    //Vertex C is positive
    //Vertex B is negative if triangle faces upwards

    QPolygonF Triangle;
    Triangle.append(QPointF(vertexA,0));
    Triangle.append(QPointF(0.,vertexB));
    Triangle.append(QPointF(vertexC,0));
    Triangle.append(QPointF(vertexA,0));
    setPolygon(Triangle);

}

Actor::Actor(double vertexA, double vertexB, double vertexC, double distortion)
    : QGraphicsPolygonItem() {

    //Left Point
    this->vertexA = int(abs(vertexA * distortion));
    //Horizontal
    this->vertexB = int(abs(vertexB * distortion));
    //Right Point
    this->vertexC = int(abs(vertexC * distortion));

    //Vertex A is negative
    //Vertex C is positive
    //Vertex B is negative if triangle faces upwards

    QPolygonF Triangle;
    Triangle.append(QPointF(vertexA,0));
    Triangle.append(QPointF(0.,vertexB));
    Triangle.append(QPointF(vertexC,0));
    Triangle.append(QPointF(vertexA,0));
    setPolygon(Triangle);

}

double Actor::getHeight()
{
    return vertexB;
}

double Actor::getWidth()
{
    return (vertexA + vertexC);
}

double Actor::getDistortion()
{
    return distortion;
}
