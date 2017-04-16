#ifndef GAMELOOP_H
#define GAMELOOP_H
#include "state.h"
#include "player.h"

class gameLoop : public State, public QObject
{
        Q_OBJECT
private:


public:
    Player * player;
    gameLoop(int x, int y);
    show();
    displayMainMenu();
    int roundcount = 1;
public slots:
    spawn();
    nextround();
};

#endif // GAMELOOP_H
