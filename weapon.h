#ifndef WEAPON_H
#define WEAPON_H

#include <QObject>
#include <QTimer>
#include <string>

class Player;

class Weapon: public QObject
{
    Q_OBJECT
private:
    std::string name;
    QTimer* fireRate;
    Player* owner;
    bool canFire;
    bool canSpread;
    int numberOfPellets;

public:
    Weapon(int rate, Player* owner);
    //Create Spreading Weapon, Overloaded Constructor
    Weapon(int rate, Player* owner, int pellets);
    bool getCanFire();
    void setCanFire(bool a);
    std::string getName();
public slots:
    void shoot();

};

#endif // WEAPON_H
