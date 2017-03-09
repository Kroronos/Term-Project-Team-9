#ifndef STATE_H
#define STATE_H
#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "player.h"


class State
{
private:
    int xDimension;
    int yDimension;
public:
    QGraphicsScene* sScene;
    QGraphicsView* sView;
    State(int x, int y);
    //Inserts sScene into sView
    void setSceneInView();
    //Displays sView
    void showView();
    //Add Item Default : sets item at (0,0) pxl dimenstions
    void addItem(QGraphicsItem* item);
    //Overloaded: addsPlayer, sets the, at starting position
    void addItem(Player* player);
};

#endif // STATE_H
