#include "gameloop.h"
#include "state.h"
#include "enemy.h"
#include "player.h"
#include "game.h"
#include "score.h"
#include "health.h"

#include <QObject>
#include <QTimer>
#include <stdlib.h>
#include <QtCore>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QGraphicsScene>

extern Game * game;
gameLoop::gameLoop(int x, int y)
    :State(x,y)
{
    //Create Player
    player = new Player(":/Images/Images/Player_Straight5.png",getScaling());
    //realPlayer = *player;

    //Add Player To Scene
    addItem(player);

    //Makes Player allowed to become focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    //Allows Player to receive input
    player->setFocus();
        
     //creating score and health
    score = new Score();
    sScene->addItem(score);
    health = new Health();
    health->setPos(health->x(), health->y()+25);
    sScene->addItem(health);

    setSceneInView();
    showView();

    if(roundcount > 6){
        //code for the end of the game
    }
    else{

        //Everything after this belongs to you wesley
        QTimer *roundtimer = new QTimer();
        QTimer *enemytimer = new QTimer();

        QObject::connect(enemytimer,SIGNAL(timeout()), this, SLOT(spawn()));
        QObject::connect(roundtimer,SIGNAL(timeout()), this, SLOT(nextround()));
        roundtimer->start(180000); //This sets the round timer to 3 minutes
        enemytimer->start(5000); //We can adjust this number for difficulty

    }
}

gameLoop::show() //idk what this is supposed to do
{

}

gameLoop::displayMainMenu() //idk what this is supposed to do
{

}

gameLoop::spawn()
{
    enemy* enemyarray[5];
    int random_pos = rand() % 1792; //Width of the screen - 128
    int randomenemy = rand() % 6;
    enemyarray[randomenemy]->setPos(random_pos, -128); //This number will be the negative height of the tallest enemy
    addItem(enemyarray[randomenemy]);
}

gameLoop::nextround()
{
    //makes realplayer equivalent to player in scene
    //realPlayer = *player;

    //removes and deletes items from scene
    clearScene();

    //*player = realPlayer;
    //re-add player to scene
    addItem(player);

    //Makes Player allowed to become focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    //Allows Player to receive input
    player->setFocus();

    setSceneInView();
    showView();
}

