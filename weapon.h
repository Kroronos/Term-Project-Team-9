#ifndef WEAPON_H
#define WEAPON_H

#include <QObject>
#include <QTimer>

class Player;

class Weapon: public QObject
{
    Q_OBJECT
private:
    QTimer* fireRate;
    bool canFire;
    Player* owner;

public:
    Weapon(int rate, Player* owner);
    bool getCanFire();
    void setCanFire(bool a);
public slots:
    void shoot();

};

#endif // WEAPON_H
