#ifndef MAINMENU_H
#define MAINMENU_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

class mainMenu: public QGraphicsRectItem, public QObject{

    Q_OBJECT
public:
    //constructors
    mainMenu(QString name, QGraphicsItem* parent=NULL);

    //public methods (events)
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void clicked();

public slots:
    void start();
    void close();
    void displayPauseMenu();
    void returnToGame();
    void replayGame();
private:
    QGraphicsTextItem * text;

};

#endif // MAINMENU_H
