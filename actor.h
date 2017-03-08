#ifndef ACTOR_H
#define ACTOR_H
#include <QtCore>
#include <QGraphicsPolygonItem>

class Actor: public QGraphicsPolygonItem
{
public:
    Actor(double vertexA, double vertexB, double vertexC);
    Actor(QPolygonF poly);
};

#endif // ACTOR_H
