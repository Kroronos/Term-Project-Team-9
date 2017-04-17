#include "sounds.h"
#include <QFileInfo>
#include <QDir>
#include <QtMultimedia>
#include <QtMultimediaWidgets>


void sounds::playBullet()
{
    QSound::play(":/sounds/sounds/laser.aiff");
}

void sounds::playExplosion()
{
    QSound::play(":/sounds/sounds/explosion.mp3");
}

void sounds::playRound(int round)
{
    switch (round) {

        case 1:
            QSound::play(":/sounds/sounds/Visager_-_05_-_Battle.mp3");
            break;
        case 2:
            //QSound::stop();
            QSound::play(":/sounds/sounds/Captive_Portal_-_06_-_Is_It_Minus_5.mp3");
            break;
        case 3:
            //QSound::stop();
            QSound::play(":/sounds/sounds/Visager_-_01_-_Title_Theme.mp3");
            break;
        case 4:
            //QSound::stop();
            QSound::play(":/sounds/sounds/GoCart - Drop Mix.mp3");
            break;
        case 5:
            //QSound::stop();
            QSound::play(":/sounds/sounds/Azureflux_-_04_-_I_Ate_All_The_Snacks.mp3");
            break;
        case 6:
            //QSound::stop();
            QSound::play(":/sounds/sounds/Visager_-_08_-_Winter_Village.mp3");
            break;


    }
}
