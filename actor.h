#ifndef ACTOR_H
#define ACTOR_H
#include <QtCore>
#include <QGraphicsPolygonItem>

class Actor: public QGraphicsPolygonItem
{
private:
    unsigned int vertexA;
    unsigned int vertexB;
    unsigned int vertexC;
public:
    Actor(double vertexA, double vertexB, double vertexC);
    double getHeight();
    double getWidth();
};

#endif // ACTOR_H
