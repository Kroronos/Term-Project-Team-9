#ifndef ACTOR_H
#define ACTOR_H
#include <QtCore>
#include <QGraphicsPolygonItem>

class Actor
{
public:
    QGraphicsPolygonItem* pTriangleItem;
    //Creates a triangle with three vetices
    Actor(double vertexA, double vertexB, double vertexC);
};

#endif // ACTOR_H
