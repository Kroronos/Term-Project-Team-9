#include "enemy.h"

#include <stdlib.h>

enemy::enemy(enemy random)
{

}

void enemy::spawn()
{
    int random_pos = rand() % 672; //This number will be ViewWidth - the width of the widest enemy
    setPos(random_pos, 0); //This number will be the negative height of the tallest enemy
    //this function needs an array of enemies to randomly pull from
    int randomenemy = rand() % 8; //this makes it so it pulls randomly from one of the seven enemies
    enemy * Enemy = new enemy;
    scene()->addItem();
}
