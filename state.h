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
    //fractional difference betweeen 1920 and current resolution
    int distortion;
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
    //Overloaded: addsPlayer, sets player at appropriate starting position
    void addItem(Player* player);
    //Calculates how much pixel by pixel, the scene varies from 1920 by 1080 dev environment
    void calculateDistortion();
    double getDistortion();
};

#endif // STATE_H
