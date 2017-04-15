#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QBasicTimer>
#include <QObject>


#include "mainmenu.h"
#include "score.h"
#include "health.h"
#include "gameloop.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    //constructors
    Game(QWidget* parent=NULL);

    //public methods
    void displayMainMenu();
    void gameOver();
    void displayGameOverWindow(QString textToDisplay);
    void pause();
    void displayPauseMenu(QString displayText);

    //public attributes
    QGraphicsScene* scene;

    //pointer for score
    Score *score;

    //pointer for health
    Health * health;

    //global game accesor
    gameLoop * startGame;




public slots:
    void start();
    void replayGame();
    void returnToGame();


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
};

#endif // GAME_H
