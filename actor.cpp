#include "actor.h"
#include <cmath>
#include <QtCore>
#include <QGraphicsPolygonItem>
#include <QDebug>

//Triangle Constructor
Actor::Actor(double vertexA, double vertexB, double vertexC, double scaling)
    : QGraphicsPolygonItem() {

    //Set scaling
    this->scaling = scaling;
    qDebug() << scaling;
    //Left Point
    this->vertexA = int(abs(vertexA * scaling));
    //Horizontal
    this->vertexB = int(abs(vertexB * scaling));
    //Right Point
    this->vertexC = int(abs(vertexC * scaling));

    //Vertex A is negative
    //Vertex C is positive
    //Vertex B is negative if triangle faces upwards

    QPolygonF Triangle;
    Triangle.append(QPointF(vertexA * scaling,0));
    Triangle.append(QPointF(0,vertexB * scaling));
    Triangle.append(QPointF(vertexC * scaling,0));
    Triangle.append(QPointF(vertexA * scaling,0));
    setPolygon(Triangle);

}

//Rectangle Costructor
Actor::Actor(double vertexA, double vertexB, double scaling)
    :QGraphicsPolygonItem() {

    //Set scaling
    this->scaling = scaling;

    //Width
    this->vertexA = int(abs(vertexA*scaling));
    this->vertexC = this->vertexA;
    //Height
    this->vertexB = int(abs(vertexB*scaling));


    QPolygonF Rectangle;
    Rectangle.append(QPointF(vertexA*scaling,vertexB*scaling));
    Rectangle.append(QPointF(vertexA*scaling, 0));
    Rectangle.append(QPointF(0,0));
    Rectangle.append(QPointF(0,vertexB*scaling));

    setPolygon(Rectangle);

}

//Circle Costructor
Actor::Actor(double radius, double scaling)
    :QGraphicsPolygonItem() {

    //Set scaling
    this->scaling = scaling;

    //Calculate right, left, and upper vertices for calculations
    this->vertexA = int(abs(radius*scaling));
    this->vertexB = (this->vertexA)*2;
    this->vertexC = this->vertexA;

    QPolygonF Circle;
    //x^2 + y^2 = radius^2
    //Q1
    for(double i = 0; i < radius; ++i) {
        Circle.append(QPointF((radius - i)*scaling, (sqrt(pow(radius,2) - pow(radius-i, 2))*scaling)));
    }
    //Q2
    for(double i = 0; i < radius; ++i) {
        Circle.append(QPointF((-1*sqrt(pow(radius,2) - pow(radius-i, 2))*scaling), ((radius - i)*scaling)));
    }
    //Q3
    for(double i = 0; i < radius; ++i) {
        Circle.append(QPointF(-1* ((radius - i)*scaling), (-1*sqrt(pow(radius,2) - pow(radius-i, 2))*scaling)));
    }
    //Q4
    for(double i = 0; i < radius; ++i) {
        Circle.append(QPointF((sqrt(pow(radius,2) - pow(radius-i, 2))*scaling),-1* ((radius - i)*scaling)));
    }

    setPolygon(Circle);
}


double Actor::getHeight()
{
    return vertexB;
}

double Actor::getWidth()
{
    return (vertexA + vertexC);
}

double Actor::getScaling()
{
    return scaling;
}
