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
#include "rounds.h"


class gameLoop : public QGraphicsView, public State
{

    Q_OBJECT

private:
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    int timeoutTime();

    QBasicTimer timer;
    QTimer *roundTimer;
    QTimer * spawnTimer;

   // QPointer <QLabel> nextPieceLabel;
    bool isStarted;
    bool isPaused;
    int level;


public:
    //vectors used to track objects on screen
    std::vector<Bullet*> Bullets;
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

    //Used to safely delete enemy, without causing nullptr exception, needs enemies to be in vector Enemies
    void deleteEnemy(QGraphicsItem* hitEnemy);

    //Protocols used to halt objects for pause
    void pauseEnemy(QGraphicsItem* pausedEnemy);
    void unpauseEnemy(QGraphicsItem* pausedEnemy);
    void pauseBullet(QGraphicsItem* pausedBullet);
    void unpauseBullet(QGraphicsItem* pausedBullet);

    //used to pause game and halt spawn and round timers
    void pauseSpawnTimer();
    void startSpawnTimer();
    void pauseRoundTimer();
    void startRoundTimer();

    //public attributes
    QGraphicsScene* scene;

    //pointer for score
    Score *score;
    rounds* round;


    //main menu buttons
    mainMenu* resumeGame;
    mainMenu* quit;
    mainMenu* play;
    mainMenu* playAgain;
    mainMenu* pauseGame;

    //Round Counter
    int roundCount = 0;
    double speedModifer;

public slots:
    void spawn();
    void start();
    void close();
    void nextRound();
    void replayGame();
    void returnToGame();
    void displayPauseMenu();
};

#endif // GAMELOOP_H
