//this is the second wesley patch
#include "gameloop.h"
#include "state.h"
#include "score.h"
#include "health.h"
#include "enemy.h"
#include "mainmenu.h"
#include "state.h"
#include <QGraphicsPixmapItem>
#include <QCoreApplication>
#include <QPixmap>
#include <QDebug>
#include <QTime>
#include <vector>
#include "enemyone.h"
#include "enemytwo.h"
#include "enemythree.h"
#include "enemyfour.h"
#include "actor.h"

extern gameLoop * globalGame;
mainMenu* play;

gameLoop::gameLoop(int x, int y)
    :State(x,y)
{
    //Create Player
    player = new Player(":/Images/Images/Player_Straight5.png",getScaling());

 //   addItem(player);

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
    scene1 = new QGraphicsScene();
    scene1->setSceneRect(0, 0, 1920, 1080);
    setScene(scene1);

    //create score and health
    score = new Score();
    scene1->addItem(score->scoreBoard);
    //ealth = new Health();
    player->health->text->setPos(player->health->text->x(), player->health->text->y()+25);
    scene1->addItem(player->health->text);
    player->setPos(x/2, y - 1.1*(player->getHeight()));
    scene1->addItem(player);
    enemyThree* enemy = new enemyThree(1);
    scene1->addItem(enemy);
    Enemies.push_back(enemy);
    enemyFour* enemy2 = new enemyFour(1);
    scene1->addItem(enemy2);
    Enemies.push_back(enemy2);
    pause();

    setSceneInView();
    showView();

    QTimer *roundtimer = new QTimer();
    QTimer *enemytimer = new QTimer();

    connect(enemytimer,SIGNAL(timeout()), this, SLOT(spawn()));
    //QObject::connect(roundtimer,SIGNAL(timeout()), this, SLOT(nextround()));
    //roundtimer->start(180000); //This sets the round timer to 3 minutes
    enemytimer->start(5000); //We can adjust this number for difficulty
}

void gameLoop::show()
{

}

void gameLoop::start(){

    //clear the screen
    play->close();
    globalGame = new gameLoop(1920, 1080);
    score = 0;
    level = 1;  //start at level 1
    player->health->resetHealth();

}

void gameLoop::replayGame()
{
    scene1->removeItem(player);
    foreach(QGraphicsItem* a, scene1->items()) {
        deleteEnemy(a);
    }

    scene1->clear();
    start();
}

void gameLoop::returnToGame(){

    foreach(QGraphicsItem* a, scene1->items()){
        a->setEnabled(true);
        unpauseEnemy(a);
    }

    player->startFastTimer();
    /*   //pause menu return to game
    if (!isStarted)
        return;
    isPaused = !isPaused;
    if (isPaused){
        timer.stop();
    } else {
        timer.start(timeoutTime(), this);
    }
    update();
*/
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
    scene1->addItem(panel);
}

void gameLoop::displayMainMenu(){
    //create the title
    QGraphicsTextItem* title = new QGraphicsTextItem(QString("Initiative #9"));
    QFont titleFont("comic sans", 50);
    title->setFont(titleFont);
    int titlexPos = this->width()/2 - title->boundingRect().width()/2;
    int titleyPos = 150;
    title->setPos(titlexPos, titleyPos);
    scene1->addItem(title);

    //create the play button
    play = new mainMenu(QString ("Play"));
    int buttonxPos = this->width()/2 - play->boundingRect().width()/2;
    int buttonyPos = 275;
    play->setPos (buttonxPos, buttonyPos);
    connect(play, SIGNAL(clicked()), this, SLOT(start()));
    scene1->addItem(play);

    //create the quit button
    mainMenu* quit = new mainMenu(QString ("Quit"));
    int bxPos = this->width()/2 - quit->boundingRect().width()/2;
    int byPos = 350;
    quit->setPos(bxPos, byPos);
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    scene1->addItem((quit));



}

void gameLoop::pause()
{
    //create pause button on game screen
    mainMenu* pauseGame = new mainMenu(QString ("Pause"));
    int buttonxPos = 1710/*this->width()/2 - pauseGame->boundingRect().width()/2*/;
    int buttonyPos = 5;
    pauseGame->setPos (buttonxPos, buttonyPos);
    scene1->addItem(pauseGame);
    connect(pauseGame, SIGNAL(clicked()), this, SLOT(displayPauseMenu()));

}

void gameLoop::displayPauseMenu(/*QString displayText*/)
{

   // freeze();
    QString message2;
    message2 = "Game Paused";

    //disable scene items
    foreach(QGraphicsItem* a, scene1->items()){
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
    scene1->addItem(resumeGame);
    connect(resumeGame, SIGNAL (clicked()), this, SLOT(returnToGame()));

    //create quit button
    mainMenu* quit = new mainMenu (QString ("Quit"));
    quit->setPos(840,500);
    scene1->addItem(quit);
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));

    //create text
    QGraphicsTextItem *pausedText = new QGraphicsTextItem(message2);
    QFont titleFont("comic sans", 25);
    pausedText->setFont(titleFont);
    pausedText->setPos (780, 300);
    scene1->addItem(pausedText);

    isStarted = true;


}
 /*
void freeze() {
    //Freezes all events
    QTime pauseTime = QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < pauseTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}*/

void gameLoop::gameOver()  //player health is 0
{
    QString message;
    message = "You lost!";

    displayGameOverWindow(message);
}

void gameLoop::displayGameOverWindow(QString textToDisplay)
{
    //disable scene items
    foreach(QGraphicsItem* a, scene1->items()){
        a->setEnabled(false);
        pauseEnemy(a);
    }
    player->stopFastTimer();

    //semi transparent panel
    drawPanel(0, 0, 1920, 1080, Qt::black, 0.65);

    //draw panel
    drawPanel(740, 300, 400, 400, Qt::lightGray, 0.75);

    //create playAgain button
    mainMenu* playAgain = new mainMenu(QString ("Play Again"));
    playAgain->setPos(840, 400);
    scene1->addItem(playAgain);
    connect(playAgain, SIGNAL (clicked()), this, SLOT(replayGame()));

    //create quit button
    mainMenu* quit = new mainMenu (QString ("Quit"));
    quit->setPos(840,500);
    scene1->addItem(quit);
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));

    //create text
    QGraphicsTextItem *gameOverText = new QGraphicsTextItem(textToDisplay);
    gameOverText->setPos (500, 225);
    QFont titleFont("comic sans", 25);
    gameOverText->setFont(titleFont);
    gameOverText->setPos (785, 300);
    scene1->addItem(gameOverText);
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

void gameLoop::pauseEnemy(QGraphicsItem* pausedEnemy) {
    for(int i = 0; i < Enemies.size(); ++i) {
        if(Enemies[i] == pausedEnemy) {
            Enemies[i]->stopShooting();
            Enemies[i]->stopMoving();
        }
    }
}

void gameLoop::unpauseEnemy(QGraphicsItem* pausedEnemy) {
    for(int i = 0; i < Enemies.size(); ++i) {
        if(Enemies[i] == pausedEnemy) {
            Enemies[i]->startsShooting();
            Enemies[i]->startsMoving();
        }
    }
}

void gameLoop::spawn()
{
    int random_pos = rand() % 1792; //Width of the screen - 128
    int randomenemy = rand() % 6;
    if(randomenemy == 1){
        Enemy *newenemy = new Enemy("", 1);
        newenemy->setPos(random_pos, -128);
        scene()->addItem(newenemy);
        Enemies.push_back(newenemy);
    }
    else if(randomenemy == 2){
        enemyOne *newenemy = new enemyOne(1);
        newenemy->setPos(random_pos, -128);
        scene()->addItem(newenemy);
        Enemies.push_back(newenemy);
    }
    else if(randomenemy == 3){
        enemyTwo *newenemy = new enemyTwo(1);
        newenemy->setPos(random_pos, -128);
        scene()->addItem(newenemy);
        Enemies.push_back(newenemy);
    }
    else if(randomenemy == 4){
        enemyThree *newenemy = new enemyThree(1);
        newenemy->setPos(random_pos, -128);
        scene()->addItem(newenemy);
        Enemies.push_back(newenemy);
    }
    else if(randomenemy == 5){
        enemyFour *newenemy = new enemyFour(1);
        newenemy->setPos(random_pos, -128);
        scene()->addItem(newenemy);
        Enemies.push_back(newenemy);
    }
}

void gameLoop::nextround()
{

}
