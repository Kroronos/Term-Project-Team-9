#ifndef MAINMENU_H
#define MAINMENU_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

class mainMenu: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    //constructors
    mainMenu(QString name, QGraphicsItem* parent=NULL);

    //public methods (events)
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void setMainFont(QFont font);
    void setMainColor(QColor a);
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
