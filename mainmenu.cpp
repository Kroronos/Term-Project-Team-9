#include "mainmenu.h"
#include <QGraphicsTextItem>
#include <QBrush>

mainMenu::mainMenu(QString name, QGraphicsItem *parent) : QGraphicsRectItem(parent){
    //draw the rectangle
    setRect(0,0,200,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkMagenta);
    setBrush(brush);

    //draw text
    text = new QGraphicsTextItem(name, this); //when button is deleted, so is the text
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos, yPos);

    //allow responding to hover events
    setAcceptHoverEvents(true);
}

void mainMenu::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();

}

void mainMenu::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //change color to magenta
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::magenta);
    setBrush(brush);
}

void mainMenu::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    //change to dark magenta
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkMagenta);
    setBrush(brush);
}

void mainMenu::start()
{

}

void mainMenu::close()
{

}

void mainMenu::displayPauseMenu()
{

}

void mainMenu::returnToGame()
{

}

void mainMenu::replayGame()
{

}
