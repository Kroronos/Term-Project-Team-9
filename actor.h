#ifndef ACTOR_H
#define ACTOR_H
#include <QtCore>
#include <QGraphicsPixmapItem>

class Actor: public QObject, public QGraphicsPixmapItem
{
private:
    double scaling = 1;
    QRectF boundingRectRef;
public:
    Actor(const QString &fileName, double scaling);

    double getHeight();
    double getWidth();
    double getScaling();
};

#endif // ACTOR_H
