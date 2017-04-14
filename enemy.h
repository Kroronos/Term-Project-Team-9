#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>


class enemy : public QObject, public actor
{
Q_OBJECT
public:
    enemy();
public slots:
    void spawn();
};

#endif // ENEMY_H
