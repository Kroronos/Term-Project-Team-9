#ifndef ACTOR_H
#define ACTOR_H
#include <QtCore>
#include <QGraphicsPolygonItem>

class Actor: public QGraphicsPolygonItem
{
private:
    unsigned int vertexA = 0;
    unsigned int vertexB = 0;
    unsigned int vertexC = 0;
    unsigned int vertexD = 0;
    double scaling = 1;
public:
    //Constructor for triangle with scaling
    Actor(double vertexA, double vertexB, double vertexC, double scaling);

    //Constructor for rectangle with scaling
    Actor(double vertexA, double vertexB, double scaling);

    //Constructor for circle(approximated) with scaling
    Actor(double radius, double scaling);

    double getHeight();
    double getWidth();
    double getScaling();
};

#endif // ACTOR_H
