#ifndef STATE_H
#define STATE_H
#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsView>

class State
{
public:
    QGraphicsScene* sScene;
    QGraphicsView* sView;
    State();
    //Inserts sScene into sView
    void setSceneInView();
    //Displays sView
    void showView();
};

#endif // STATE_H
