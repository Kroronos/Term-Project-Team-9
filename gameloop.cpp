#include "gameloop.h"
#include "state.h"
#include "score.h"
#include "health.h"
#include "enemy.h"
#include "mainmenu.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>

gameLoop * game;

gameLoop::gameLoop(int x, int y)
    :State(x,y)
{
    //Create Player
    player = new Player(":/Images/Images/Player_Straight5.png",getScaling());

    //Add Player To Scene

    addItem(player);

    //Makes Player allowed to become focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    //Allows Player to receive input
    player->setFocus();

    //set up screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1920,1080);
    showFullScreen();

    //set up scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1920, 1080);
    setScene(scene);

    //create score and health
    score = new Score();
    scene->addItem(score);
    health = new Health();
    health->setPos(health->x(), health->y()+25);
    scene->addItem(health);

    setSceneInView();
    showView();


}

void gameLoop::show()
{

}

void gameLoop::start(){

    game = new gameLoop(1920, 1080);
    //clear the screen
    score = 0;
    level = 1;  //start at level 1
    health->resetHealth();

}

void gameLoop::replayGame()
{
    scene->clear();
    start();
}

void gameLoop::returnToGame(){
    //pause menu return to game
    if (!isStarted)
        return;
    isPaused = !isPaused;
    if (isPaused){
        timer.stop();
    } else {
        timer.start(timeoutTime(), this);
    }
    update();
}

void gameLoop::drawPanel(int x, int y, int width, int height, QColor color, double opacity)
{
    //draw a panel
    QGraphicsRectItem * panel = new QGraphicsRectItem(x, y, width, height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity); //high values not transparent
    scene->addItem(panel);
}

void gameLoop::displayMainMenu(){
    //create the title
    QGraphicsTextItem* title = new QGraphicsTextItem(QString("Initiative #9"));
    QFont titleFont("comic sans", 50);
    title->setFont(titleFont);
    int titlexPos = this->width()/2 - title->boundingRect().width()/2;
    int titleyPos = 150;
    title->setPos(titlexPos, titleyPos);
    scene->addItem(title);

    //create the play button
    mainMenu* play = new mainMenu(QString ("Play"));
    int buttonxPos = this->width()/2 - play->boundingRect().width()/2;
    int buttonyPos = 275;
    play->setPos (buttonxPos, buttonyPos);
    connect(play, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(play);

    //create the quit button
    mainMenu* quit = new mainMenu(QString ("Quit"));
    int bxPos = this->width()/2 - quit->boundingRect().width()/2;
    int byPos = 350;
    quit->setPos(bxPos, byPos);
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem((quit));



}

void gameLoop::pause()
{
    //create pause button on game screen
    mainMenu* pauseGame = new mainMenu(QString ("Pause"));
    int buttonxPos = this->width()/2 - pauseGame->boundingRect().width()/2;
    int buttonyPos = 275;
    pauseGame->setPos (buttonxPos, buttonyPos);
     scene->addItem(pauseGame);
    connect(pauseGame, SIGNAL(clicked()), this, SLOT(displayPauseMenu()));

    QString message2;
    message2 = "Game Paused";

    displayGameOverWindow(message2);


}

void gameLoop::displayPauseMenu(QString displayText)
{
    //disable scene items
    for (size_t i = 0, n = scene->items().size(); i < n; i++){
        scene->items()[i]->setEnabled(false);
    }

    //semi transparent panel
    drawPanel(0, 0, 1024, 768, Qt::black, 0.65);

    //draw panel
    drawPanel(312, 184, 400, 400, Qt::lightGray, 0.75);

    //create Resume button
    mainMenu* resumeGame = new mainMenu(QString ("Resume"));
    resumeGame->setPos(410, 300);
    scene->addItem(resumeGame);
    connect(resumeGame, SIGNAL (clicked()), this, SLOT(returnToGame()));

    //create quit button
    mainMenu* quit = new mainMenu (QString ("Quit"));
    quit->setPos(410,375);
    scene->addItem(quit);
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));

    //create text
    QGraphicsTextItem *pausedText = new QGraphicsTextItem(displayText);
    pausedText->setPos (460, 225);
    scene->addItem(pausedText);
}

void gameLoop::gameOver()  //player health is 0
{
    QString message;
    message = "You lost!";

    displayGameOverWindow(message);
}

void gameLoop::displayGameOverWindow(QString textToDisplay)
{
    //disable scene items
    for (size_t i = 0, n = scene->items().size(); i < n; i++){
        scene->items()[i]->setEnabled(false);
    }

    //semi transparent panel
    drawPanel(0, 0, 1024, 768, Qt::black, 0.65);

    //draw panel
    drawPanel(312, 184, 400, 400, Qt::lightGray, 0.75);

    //create playAgain button
    mainMenu* playAgain = new mainMenu(QString ("Play Again"));
    playAgain->setPos(410, 300);
    scene->addItem(playAgain);
    connect(playAgain, SIGNAL (clicked()), this, SLOT(replayGame()));

    //create quit button
    mainMenu* quit = new mainMenu (QString ("Quit"));
    quit->setPos(410,375);
    scene->addItem(quit);
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));

    //create text
    QGraphicsTextItem *gameOverText = new QGraphicsTextItem(textToDisplay);
    gameOverText->setPos (500, 225);
    scene->addItem(gameOverText);
}

void gameLoop::deleteEnemy(QGraphicsItem* hitEnemy)
{
    for(int i = 0; i < Enemies.size(); ++i) {
        if(Enemies[i] == hitEnemy) {
            sScene->removeItem(Enemies[i]);
            delete Enemies[i]->myEnemyWeapon;
            delete Enemies[i];
        }
    }
}

void gameLoop::spawn()
{

}

void gameLoop::nextround()
{

}
