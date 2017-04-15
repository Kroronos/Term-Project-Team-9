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
    double scaling;

public:

    Weapon(int rate, Player* owner, double scaling);

    //Create Spreading Weapon, Overloaded Constructor
    Weapon(int rate, Player* owner, int pellets, double scaling);


    bool getCanFire();
    void setCanFire(bool a);
    std::string getName();
public slots:
    void shoot();

};

#endif // WEAPON_H
