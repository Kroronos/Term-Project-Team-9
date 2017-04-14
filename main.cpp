#include <QApplication>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QGraphicsView>
#include <QtCore>
#include "state.h"
#include "actor.h"
#include "player.h"
#include "bullet.h"
#include "gameloop.h"
#include "game.h"

gameLoop * globalGame;
Game *game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    globalGame = new gameLoop(1920, 1080);
    
    game = new Game();
    
    game -> show();
    
    game -> displayMainMenu();

    return a.exec();


}
