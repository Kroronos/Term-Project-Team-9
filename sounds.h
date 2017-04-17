#ifndef SOUNDS_H
#define SOUNDS_H

#include <QSound>

class sounds {

    public:
       static void playBullet();
       static void playExplosion();
       static void playRound(int round);

};


#endif // SOUNDS_H
