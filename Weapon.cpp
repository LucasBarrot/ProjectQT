#include "Weapon.h"
#include "Game.h"

#include <QGraphicsScene>
#include <QDebug>

extern Game * game;

Weapon::Weapon(){
    QImage img(":/Source/Source/Image/Weapon/weapon_red_magic_staff.png");
    img = img.scaled(4, 10);
    setPixmap(QPixmap::fromImage(img));
    setTransformOriginPoint(img.width()/2, img.height()/2);

    rateOfFirePerSeconde = 2;
}

void Weapon::Shoot()
{
    timer = new QTimer();
    connect(timer,&QTimer::timeout,this,&Weapon::continuToShoot);
    continuToShoot();
    timer->start(1000/rateOfFirePerSeconde);
}

void Weapon::continuToShoot()
{
    if(game->mousePressed_.size() != 0){
        Projectil * projectil = new Projectil(game->player->get_angle());
        projectil->setPos(game->player->pos() + game->player->weapon->pos());

        game->tabProjectil.append(projectil);

        qDebug() << game->player->get_angle();
        projectil->setRotation(game->player->get_angle());
        scene()->addItem(projectil);
    }
    else {
        disconnect(timer,&QTimer::timeout,this,&Weapon::continuToShoot);
    }
}


