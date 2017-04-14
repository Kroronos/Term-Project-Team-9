#ifndef GAMELOOP_H
#define GAMELOOP_H
#include "state.h"
#include "player.h"


class gameLoop : public State
{
private:
    int roundcount = 1;

public:
    Player * player;
    gameLoop(int x, int y);
};

#endif // GAMELOOP_H
