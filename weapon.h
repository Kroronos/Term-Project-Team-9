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
    bool isLaser;
    int numberOfPellets;
    double scaling;
    double bulletSize;

public:

    Weapon(int rate, Player* owner, double bulletSize, double scaling);

    //Create Spreading Weapon, Overloaded Constructor
    Weapon(int rate, Player* owner, double bulletSize, int pellets, double scaling);

    //Create Laser Weapon, Overloaded Constructor
    Weapon(Player* owner, double bulletSize, double scaling);


    bool getCanFire();
    void setCanFire(bool a);
    std::string getName();
public slots:
    void shoot();

};

#endif // WEAPON_H
