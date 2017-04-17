#include "pausemenu.h"
#include "gameloop.h"

void gameLoop::displayPauseMenu(/*QString displayText*/)
{

   // freeze();
    QString message2;
    message2 = "Game Paused";

    //disable scene items
    foreach(QGraphicsItem* a, scene->items()){
        a->setEnabled(false);
        pauseEnemy(a);
    }
    player->stopFastTimer();

    //semi transparent panel
    drawPanel(0, 0, 1920, 1080, Qt::black, 0.65);

    //draw panel
    drawPanel(740, 300, 400, 400, Qt::lightGray, 0.75);

    //create Resume button
    mainMenu* resumeGame = new mainMenu(QString ("Resume"));
    resumeGame->setPos(840, 400);
    scene->addItem(resumeGame);
    connect(resumeGame, SIGNAL (clicked()), this, SLOT(returnToGame()));

    //create quit button
    mainMenu* quit = new mainMenu (QString ("Quit"));
    quit->setPos(840,500);
    scene->addItem(quit);
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));

    //create text
    QGraphicsTextItem *pausedText = new QGraphicsTextItem(message2);
    QFont titleFont("comic sans", 25);
    pausedText->setFont(titleFont);
    pausedText->setPos (780, 300);
    scene->addItem(pausedText);

    isStarted = true;


}
