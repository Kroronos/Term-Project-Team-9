#include "sounds.h"
#include <QFileInfo>
#include <QDir>
#include <QtMultimedia>
#include <QtMultimediaWidgets>


void sounds::playBullet()
{
    QSound::play(":/sounds/sounds/laser.wav");
}

void sounds::playExplosion()
{
    QSound::play(":/sounds/sounds/explosion.wav");
}

void sounds::playRound(int round)
{
    switch (round) {

        case 1:
            QSound::play(":/sounds/sounds/Visager_-_05_-_Battle.wav");
            break;
        case 2:
            //QSound::stop();
            QSound::play(":/sounds/sounds/Captive_Portal_-_06_-_Is_It_Minus_5.wav");
            break;
        case 3:
            //QSound::stop();
            QSound::play(":/sounds/sounds/Visager_-_01_-_Title_Theme.wav");
            break;
        case 4:
            //QSound::stop();
            QSound::play(":/sounds/sounds/GoCart - Drop Mix.wav");
            break;
        case 5:
            //QSound::stop();
            QSound::play(":/sounds/sounds/Azureflux_-_04_-_I_Ate_All_The_Snacks.wav");
            break;
        case 6:
            //QSound::stop();
            QSound::play(":/sounds/sounds/Visager_-_08_-_Winter_Village.wav");
            break;


    }
}
