#ifndef WEAPON_H
#define WEAPON_H

#include <QObject>
#include <QTimer>
#include <string>

class Player;
class Enemy;

class Weapon: public QObject
{
    Q_OBJECT
private:
    std::string name;
    QTimer* fireRate;
    Player* owner;
    Enemy* ownerTwo;
    bool canFire;
    bool canSpread;
    int numberOfPellets;
    double scaling;

public:

    Weapon();

    Weapon(int rate, Player* owner, Enemy* ownerTwo, double scaling);

    //Create Spreading Weapon, Overloaded Constructor
    Weapon(int rate, Player* owner, Enemy* ownerTwo, int pellets, double scaling);

    bool getCanFire();
    void setCanFire(bool a);
    std::string getName();
public slots:
    void shoot();

};

#endif // WEAPON_H
