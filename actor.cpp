#include "actor.h"
#include <QtCore>
#include <QGraphicsPolygonItem>

Actor::Actor(double vertexA, double vertexB, double vertexC)
{
    // Describe a closed triangle
    //Vertex A is negative
    //Vertex C is positive
    //Vertex B is negative if triangle faces upwards

    QPolygonF Triangle;
    Triangle.append(QPointF(vertexA,0));
    Triangle.append(QPointF(0.,vertexB));
    Triangle.append(QPointF(vertexC,0));
    Triangle.append(QPointF(vertexA,0));
    pTriangleItem = new QGraphicsPolygonItem(Triangle);
}
