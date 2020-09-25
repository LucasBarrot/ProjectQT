#include "Explosion.h"

#include <QTimer>

#include "Game.h"

extern Game* game;

Explosion::Explosion(double argRadius){
    QImage img(":/Source/Source/Image/projectil/projectil_flame_2.png");
    img = img.scaled(argRadius, argRadius);
    setPixmap(QPixmap::fromImage(img));

    QTimer::singleShot(200, this, &Explosion::destroyExplosion);
}

void Explosion::destroyExplosion(){
    delete this;
}
