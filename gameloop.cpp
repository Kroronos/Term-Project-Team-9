#include "gameloop.h"
#include "state.h"
#include "score.h"
#include "health.h"
#include "rounds.h"
#include "enemy.h"
#include "mainmenu.h"
#include "state.h"
#include <QGraphicsPixmapItem>
#include <QCoreApplication>
#include <QPixmap>
#include <QDebug>
#include <QTime>
#include <QBrush>
#include <QImage>
#include <QPen>
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
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1920, 1080);
    setScene(scene);
    scene2 = new QGraphicsScene();
    scene2->setSceneRect(0, 0, 1920, 1080);

    //create score and health
    score = new Score();
    scene->addItem(score->scoreBoard);
    //ealth = new Health();
    player->health->text->setPos(player->health->text->x(), player->health->text->y()+25);
    scene->addItem(player->health->text);
    player->setPos(x/2, y - 1.1*(player->getHeight()));
    scene->addItem(player);
    enemyThree* enemy = new enemyThree(1);

    round = new rounds();
    scene->addItem(round->roundDisplay);


    scene->setBackgroundBrush(QBrush(QImage(":/Images/Images/space_main.jpg")));
   /* scene->addItem(enemy);
    Enemies.push_back(enemy);
    enemyFour* enemy2 = new enemyFour(1);
    scene->addItem(enemy2);
    Enemies.push_back(enemy2);
    pause();*/

    setSceneInView();
    showView();

    roundTimer = new QTimer();
    enemyTimer = new QTimer();
    connect(roundTimer,SIGNAL(timeout()), this, SLOT(nextround()));
    roundTimer->start(180000); //This sets the round timer to 3 minutes
    connect(enemyTimer,SIGNAL(timeout()), this, SLOT(spawn()));
    enemyTimer->start(2000); //This sets the round timer to 3 minutes

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
    scene->removeItem(player);
    foreach(QGraphicsItem* a, scene->items()) {
        deleteEnemy(a);
    }

    scene->clear();
    start();
}

void gameLoop::returnToGame(){

    foreach(QGraphicsItem* a, scene->items()){
        a->setEnabled(true);
        unpauseEnemy(a);
    }

    player->startFastTimer();

    scene->removeItem(resumeGame);
    //resumeGame->remove('');
    scene->removeItem(quit);
    scene->removeItem(play);
    scene->removeItem(playAgain);

    foreach(QGraphicsItem* a, scene->items()) {
        if(typeid(*a) == typeid(Player) || typeid(*a) == typeid(enemyOne) || typeid(*a) == typeid(enemyTwo) || typeid(*a) == typeid(enemyThree) || typeid(*a) == typeid(enemyFour)|| typeid(*a) == typeid(Bullet) || typeid(*a) == typeid(mainMenu) || typeid(*a) == typeid(Score)|| typeid(*a) == typeid(Health)|| typeid(*a) == typeid(QGraphicsTextItem)) {
        }
        else{
            scene->removeItem(a);
        }
    }

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
    QFont titleFont("Impact", 50);
    title->setFont(titleFont);
    title->setDefaultTextColor(QColor(Qt::black));
//    QPen outlinePen = QPen (QColor(255, 0, 0), 1, Qt::SolidLine);
 //   title->outlinePen;
    int titlexPos = this->width()/2 - title->boundingRect().width()/2;
    int titleyPos = 150;
    title->setPos(titlexPos, titleyPos);
    scene->addItem(title);

    //create the play button
    play = new mainMenu(QString ("Play"));
    int buttonxPos = this->width()/2 - play->boundingRect().width()/2;
    int buttonyPos = 400;
    play->setPos (buttonxPos, buttonyPos);
    connect(play, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(play);

    //create the quit button
    quit = new mainMenu(QString ("Quit"));
    int bxPos = this->width()/2 - quit->boundingRect().width()/2;
    int byPos = 500;
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
    resumeGame = new mainMenu(QString ("Resume"));
    resumeGame->setPos(840, 400);
    scene->addItem(resumeGame);
    connect(resumeGame, SIGNAL (clicked()), this, SLOT(returnToGame()));

    //create quit button
    quit = new mainMenu (QString ("Quit"));
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
    }
    player->stopFastTimer();

    //semi transparent panel
    drawPanel(0, 0, 1920, 1080, Qt::black, 0.65);

    //draw panel
    drawPanel(740, 300, 400, 400, Qt::lightGray, 0.75);

    //create playAgain button
    playAgain = new mainMenu(QString ("Play Again"));
    playAgain->setPos(840, 400);
    scene->addItem(playAgain);
    connect(playAgain, SIGNAL (clicked()), this, SLOT(replayGame()));

    //create quit button
    quit = new mainMenu (QString ("Quit"));
    quit->setPos(840,500);
    scene->addItem(quit);
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));

    //create text
    QGraphicsTextItem *gameOverText = new QGraphicsTextItem(textToDisplay);
    gameOverText->setPos (500, 225);
    QFont titleFont("comic sans", 25);
    gameOverText->setFont(titleFont);
    gameOverText->setPos (785, 300);
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
        scene->addItem(newenemy);
        Enemies.push_back(newenemy);
    }
    else if(randomenemy == 2){
        enemyOne *newenemy = new enemyOne(1);
        newenemy->setPos(random_pos, -128);
        scene->addItem(newenemy);
        Enemies.push_back(newenemy);
    }
    else if(randomenemy == 3){
        enemyTwo *newenemy = new enemyTwo(1);
        newenemy->setPos(random_pos, -128);
        scene->addItem(newenemy);
        Enemies.push_back(newenemy);
    }
    else if(randomenemy == 4){
        enemyThree *newenemy = new enemyThree(1);
        newenemy->setPos(random_pos, -128);
        scene->addItem(newenemy);
        Enemies.push_back(newenemy);
    }
    else if(randomenemy == 5){
        enemyFour *newenemy = new enemyFour(1);
        newenemy->setPos(random_pos, -128);
        scene->addItem(newenemy);
        Enemies.push_back(newenemy);
    }
}

void gameLoop::nextround()
{
    ++roundCount;
    round->increase();
    switch(roundCount) {
        case 1: scene->setBackgroundBrush(QBrush(QImage(":/Images/Images/space.jpg")));
            break;

        case 2: scene->setBackgroundBrush(QBrush(QImage(":/Images/Images/space_blue.png")));
            break;

        case 3: scene->setBackgroundBrush(QBrush(QImage(":/Images/Images/space_moon.jpg")));
            break;

        case 4: scene->setBackgroundBrush(QBrush(QImage(":/Images/Images/space_purple.jpg")));
            break;

        case 5: scene->setBackgroundBrush(QBrush(QImage(":/Images/Images/space_red.gif")));
            break;

    }
}
