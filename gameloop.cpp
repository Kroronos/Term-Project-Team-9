#include "gameloop.h"
#include "state.h"
#include "score.h"
#include "health.h"
#include "enemy.h"
#include "mainmenu.h"
#include "state.h"
#include "sounds.h"
#include <QGraphicsPixmapItem>
#include <QCoreApplication>
#include <QPixmap>
#include <QDebug>
#include <QTime>
#include <QBrush>
#include <QPen>
#include <QImage>
#include <vector>
#include "enemyone.h"
#include "enemytwo.h"
#include "enemythree.h"
#include "enemyfour.h"
#include "actor.h"

extern gameLoop * globalGame;

gameLoop::gameLoop(int x, int y)
    :State(x,y)
{
    player = new Player(":/Images/Images/Player_Straight5.png",getScaling());

    //set up screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1920,1080);
    showFullScreen();


    //set up scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1920, 1080);
    round = new rounds();
    speedModifer = 1;
    setScene(scene);
}

void gameLoop::show()
{

}

void gameLoop::start(){

    //clear the screen
    play->close();


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
    player = new Player(":/Images/Images/Player_Straight5.png",1);
    setScene(scene);

    //create health, score handled by bullet collisions
    player->health->text->setPos(player->health->text->x(), player->health->text->y()+25);
    scene->addItem(player->health->text);
    scene->addItem(player);
    player->setPos(0 + scene->width()/2, 0 + 4*(player->getHeight()));

    //generate rounds/round display to manage gameflow
    round = new rounds();
    speedModifer = 1;
    scene->addItem(round->roundDisplay);

    scene->setBackgroundBrush(QBrush(QImage(":/Images/Images/space_main.jpg")));

    globalGame = this;
    pause();

    setSceneInView();
    showView();


    score = 0;
    level = 1;  //start at level 1
    player->health->resetHealth();

    roundTimer = new QTimer();
    spawnTimer = new QTimer();
    //connect timers to respective slots
    connect(spawnTimer,SIGNAL(timeout()), this, SLOT(spawn()));
    connect(roundTimer,SIGNAL(timeout()), this, SLOT(nextRound()));

    //begin timers
    spawnTimer->start(2000);
    roundTimer->start(60000);

    roundCount = 0;
    scene->addItem(round->roundDisplay);
    nextRound();


}

//exits application
//exit program
void gameLoop::close()
{
    std::exit(0);
}

void gameLoop::replayGame()
{
    scene->removeItem(player);
    foreach(QGraphicsItem* a, scene->items()) {
        deleteEnemy(a);
    }

    scene->clear();
    start();
}

void gameLoop::returnToGame(){
    //unpause
    foreach(QGraphicsItem* a, scene->items()){
        a->setEnabled(true);
        unpauseEnemy(a);
        unpauseBullet(a);
    }
    startSpawnTimer();
    startRoundTimer();
    player->startFastTimer();

    scene->removeItem(resumeGame);
    //resumeGame->remove('');
    scene->removeItem(quit);
    scene->removeItem(play);

    foreach(QGraphicsItem* a, scene->items()) {
        if(typeid(*a) == typeid(Player) || typeid(*a) == typeid(enemyOne) || typeid(*a) == typeid(enemyTwo) || typeid(*a) == typeid(enemyThree) || typeid(*a) == typeid(enemyFour)|| typeid(*a) == typeid(Bullet) || typeid(*a) == typeid(mainMenu) || typeid(*a) == typeid(Score)|| typeid(*a) == typeid(Health)|| typeid(*a) == typeid(QGraphicsTextItem)) {
            //Do nothing, we want to preserve these
        }
        else{
            scene->removeItem(a);
        }
    }

    //Makes Player allowed to become focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    //Allows Player to receive input
    player->setFocus();

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

int gameLoop::timeoutTime()   //regulates speed/ time it takes for objects to fall on screen; important for pause menu
{
    return 1000/(1+level);
}

void gameLoop::displayMainMenu(){
    //create the title
    scene->setBackgroundBrush(QBrush(QImage(":/Images/Images/space_main.jpg")));
    QGraphicsTextItem* title = new QGraphicsTextItem(QString("Initiative #9"));
    QFont titleFont("Impact", 50);
    title->setFont(titleFont);
    title->setDefaultTextColor(QColor(Qt::black));

    //set title position
    int titlexPos = this->width()/2 - title->boundingRect().width()/2;
    int titleyPos = 150;
    title->setPos(titlexPos, titleyPos);
    scene->addItem(title);

    //create the play button
    play = new mainMenu(QString ("Play"));
    int buttonxPos = this->width()/2 - play->boundingRect().width()/2;
    int buttonyPos = 275;
    play->setPos (buttonxPos, buttonyPos);
    connect(play, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(play);

    //create the quit button
     quit = new mainMenu(QString ("Quit"));
    int bxPos = this->width()/2 - quit->boundingRect().width()/2;
    int byPos = 350;
    quit->setPos(bxPos, byPos);
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem((quit));



}

void gameLoop::pause()
{
    //create pause button on game screen
    pauseGame = new mainMenu(QString ("Pause"));
    int buttonxPos = 1710/*this->width()/2 - pauseGame->boundingRect().width()/2*/;
    int buttonyPos = 5;
    pauseGame->setPos (buttonxPos, buttonyPos);
    scene->addItem(pauseGame);
    connect(pauseGame, SIGNAL(clicked()), this, SLOT(displayPauseMenu()));

}

void gameLoop::displayPauseMenu(/*QString displayText*/)
{

    QFont titleFont("Times", 12);
    QFont titleFont2("Impact", 25);

   // freeze();
    QString message2;
    message2 = "Game Paused";

    //disable scene items
    foreach(QGraphicsItem* a, scene->items()){
        a->setEnabled(false);
        pauseEnemy(a);
        pauseBullet(a);
    }
    player->stopFastTimer();
    player->stopShooting();
    pauseSpawnTimer();
    pauseRoundTimer();

    //semi transparent panel
    drawPanel(0, 0, 1920, 1080, Qt::black, 0.65);

    //draw panel
    drawPanel(740, 300, 400, 325, Qt::lightGray, 0.75);

    //create Resume button
    resumeGame = new mainMenu(QString ("Resume"));
    resumeGame->setPos(840, 400);
    resumeGame->setMainFont(titleFont);
    scene->addItem(resumeGame);
    connect(resumeGame, SIGNAL (clicked()), this, SLOT(returnToGame()));

    //create quit button
    quit = new mainMenu (QString ("Quit"));
    quit->setPos(840,500);
    quit->setMainFont(titleFont);
    scene->addItem(quit);
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));

    //create text
    QGraphicsTextItem *pausedText = new QGraphicsTextItem(message2);
    pausedText->setFont(titleFont2);
    pausedText->setPos (840, 300);
    scene->addItem(pausedText);

    isStarted = true;
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
    foreach(QGraphicsItem* a, scene->items()){
        a->setEnabled(false);
        pauseEnemy(a);
        pauseBullet(a);
    }
    pauseSpawnTimer();
    pauseRoundTimer();
    player->stopShooting();
    player->stopFastTimer();

    //semi transparent panel
    drawPanel(0, 0, 1920, 1080, Qt::black, 0.65);

    //draw panel
    drawPanel(740, 300, 400, 325, Qt::lightGray, 0.75);

    //Font for buttons
    QFont titleFont("Times", 12);

    //create playAgain button
    playAgain = new mainMenu(QString ("Play Again"));
    playAgain->setPos(840, 400);
    playAgain->setMainFont(titleFont);
    scene->addItem(playAgain);
    connect(playAgain, SIGNAL (clicked()), this, SLOT(replayGame()));

    //create quit button
    quit = new mainMenu (QString ("Quit"));
    quit->setPos(840,500);
    quit->setMainFont(titleFont);
    scene->addItem(quit);
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));

    //create text
    QGraphicsTextItem *gameOverText = new QGraphicsTextItem(textToDisplay);
    QFont titleFont2("Impact", 25);
    gameOverText->setFont(titleFont2);
    gameOverText->setPos (880, 300);
    scene->addItem(gameOverText);
}

void gameLoop::deleteEnemy(QGraphicsItem* hitEnemy)
{
    for(int i = 0; i < Enemies.size(); ++i) {
        if(Enemies[i] == hitEnemy) {
            scene->removeItem(Enemies[i]);
            delete Enemies[i]->myEnemyWeapon;
            delete Enemies[i];
            Enemies.shrink_to_fit();
            return;
        }
    }
}

void gameLoop::pauseEnemy(QGraphicsItem* pausedEnemy) {
    for(int i = 0; i < Enemies.size(); ++i) {
        if(Enemies[i] == pausedEnemy) {
            if(Enemies[i]){
                Enemies[i]->stopShooting();
                Enemies[i]->stopMoving();
            }
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

void gameLoop::pauseBullet(QGraphicsItem *pausedBullet)
{
    for(int i = 0; i < Bullets.size(); ++i) {
        if(Bullets[i] == pausedBullet) {
            Bullets[i]->stopMovement();
        }
    }
}

void gameLoop::unpauseBullet(QGraphicsItem *pausedBullet)
{
    for(int i = 0; i < Bullets.size(); ++i) {
        if(Bullets[i] == pausedBullet) {
            Bullets[i]->startMovement();
        }
    }
}

void gameLoop::pauseSpawnTimer()
{
    spawnTimer->stop();
}

void gameLoop::startSpawnTimer()
{
    spawnTimer->start();
}

void gameLoop::pauseRoundTimer()
{
    roundTimer->stop();
}

void gameLoop::startRoundTimer()
{
    roundTimer->start();
}

void gameLoop::spawn()
{
    int random_pos = rand() % 1792; //Width of the screen - 128
         int randomenemy = rand() % 5;

         if(randomenemy == 1){
             enemyOne *newenemy = new enemyOne(1, speedModifer);
             newenemy->setPos(random_pos, -128);
             scene->addItem(newenemy);
             Enemies.push_back(newenemy);
         }
         else if(randomenemy == 2){
             enemyTwo *newenemy = new enemyTwo(1, speedModifer);
             newenemy->setPos(random_pos, -128);
             scene->addItem(newenemy);
             Enemies.push_back(newenemy);
         }
         else if(randomenemy == 3){
             enemyThree *newenemy = new enemyThree(1, speedModifer);
             newenemy->setPos(random_pos, -128);
             scene->addItem(newenemy);
             Enemies.push_back(newenemy);
         }
         else if(randomenemy == 4){
             enemyFour *newenemy = new enemyFour(1, speedModifer);
             newenemy->setPos(random_pos, -128);
             scene->addItem(newenemy);
             Enemies.push_back(newenemy);
         }

}

void gameLoop::nextRound()
{
    ++roundCount;
    round->increase();
    ++speedModifer;
    speedModifer += .1;
    if (roundCount == 0) {
        speedModifer = 1;
    }
    //Will Play Music Per Round
    sounds::playRound(roundCount);

    switch(roundCount) {

    case 1:
        scene->setBackgroundBrush(QBrush(QImage(":/Images/Images/space.jpg")));
        spawnTimer->start(2000);
        break;
    case 2:
        scene->setBackgroundBrush(QBrush(QImage(":/Images/Images/space_blue.png")));
        spawnTimer->start(2000/1.75);
        break;
    case 3:
        scene->setBackgroundBrush(QBrush(QImage(":/Images/Images/space_moon.jpg")));
        spawnTimer->start(2000/(1.75*1.75));
        break;
    case 4:
        scene->setBackgroundBrush(QBrush(QImage(":/Images/Images/space_purple.jpg")));
        spawnTimer->start(2000/(1.75*1.75*1.75));
        break;
    case 5:
        scene->setBackgroundBrush(QBrush(QImage(":/Images/Images/space_red.gif")));
        spawnTimer->start(2000/(1.75*1.75*1.75*1.75));
        break;
    case 6:
        player->stopFastTimer();
        player->stopShooting();
        scene->removeItem(player);
        foreach(QGraphicsItem* a, scene->items()) {
            deleteEnemy(a);
        }
        scene->clear();
        pauseRoundTimer();
        pauseSpawnTimer();
        scene->setBackgroundBrush(QBrush(QImage(":/Images/Images/space_moon.jpg")));
        QGraphicsTextItem *winText = new QGraphicsTextItem("You Win!");
        QFont titleFont("Impact", 100);
        winText->setDefaultTextColor(QColor(Qt::white));
        winText->setFont(titleFont);
        winText->setPos (500, 200);
        scene->addItem(winText);

        //draw panel
        drawPanel(740, 500, 400, 325, Qt::lightGray, 0.75);

        //Font for buttons
        QFont titleFont2("Times", 12);

        //create playAgain button
        playAgain = new mainMenu(QString ("Play Again"));
        playAgain->setPos(840, 600);
        playAgain->setMainFont(titleFont2);
        scene->addItem(playAgain);
        connect(playAgain, SIGNAL (clicked()), this, SLOT(replayGame()));

        //create quit button
        quit = new mainMenu (QString ("Quit"));
        quit->setPos(840,700);
        quit->setMainFont(titleFont2);
        scene->addItem(quit);
        connect(quit, SIGNAL(clicked()), this, SLOT(close()));

    }

}
