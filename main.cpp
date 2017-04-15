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
#include "mainMenu.h"

Game *game;
gameLoop * globalGame;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();

    game->startGame = globalGame;

    game->show();

    game->displayMainMenu();

    return a.exec();


}
