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
    double distortion = 1;
public:
    Actor(double vertexA, double vertexB, double vertexC);
    Actor(double vertexA, double vertexB, double vertexC, double distortion);
    double getHeight();
    double getWidth();
    double getDistortion();
};

#endif // ACTOR_H
