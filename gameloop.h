#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QBasicTimer>
#include <QObject>
#include <vector>


#include "mainmenu.h"
#include "score.h"
#include "health.h"
#include "state.h"
#include "player.h"


class gameLoop : public QGraphicsView, public State
{

    Q_OBJECT

private:
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    int timeoutTime()   //regulates speed/ time it takes for objects to fall on screen; important for pause menu
    {
        return 1000/(1+level);
    }

    QBasicTimer timer;
   // QPointer <QLabel> nextPieceLabel;
    bool isStarted;
    bool isPaused;
    int level;


public:
    std::vector<Enemy*> Enemies;
    Player * player;
    gameLoop(int x, int y);
    void show();
    int roundcount = 1;

    //public methods
    void displayMainMenu();
    void gameOver();
    void displayGameOverWindow(QString textToDisplay);
    void pause();
 //   void freeze();
    void deleteEnemy(QGraphicsItem* hitEnemy);

    void pauseEnemy(QGraphicsItem* pausedEnemy);
    void unpauseEnemy(QGraphicsItem* pausedEnemy);

    //public attributes
    QGraphicsScene* scene;
    QGraphicsScene* scene2;
    QGraphicsScene* scene3;

    //main menu buttons
    mainMenu* resumeGame;
    mainMenu* quit;
    mainMenu* play;
    mainMenu* playAgain;
    mainMenu* pauseGame;

    //pointer for score
    Score *score;

public slots:
    void spawn();
    void nextround();
    void start();
    void replayGame();
    void returnToGame();
    void displayPauseMenu();
};

#endif // GAMELOOP_H
