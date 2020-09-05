#include "Weapon.h"
#include "Game.h"

#include <QGraphicsScene>
#include <QDebug>

extern Game * game;

Weapon::Weapon(double argXOriginPlayer, double argYOriginPlayer){
    //set image of the weapon
    img = QImage(":/Source/Source/Image/Weapon/weapon_red_magic_staff.png");
    img = img.scaled(4, 10);
    setPixmap(QPixmap::fromImage(img));

    setTransformOriginPoint(img.width()/2, img.height()/2);

    //set position caracter
    pointPosWeapon = QPointF(16-4, 10);
    setPos(pointPosWeapon);


    setParent(NULL);

    //Draw a line Line to know where to shoot
    lineRotationWeapon.setP1(-QPointF(argXOriginPlayer, argYOriginPlayer) + pointPosWeapon + QPointF(img.width()/2, img.height()/2));
    lineRotationWeapon.setP2(-QPointF(argXOriginPlayer, argYOriginPlayer) + pointPosWeapon + QPointF(0,0));


    //set rate of fire
    rateOfFirePerSeconde = 2;

    //set verif if timer of the special shoot is ready
    specialShootReady = true;

    //set a condition, if timer of simple shoot is over you can shoot again
    simpleShootReady = true;

    //setTransformOriginPoint(img.width()/2, img.height()/2);

    //set timer continous shooting
    timer = new QTimer();
    connect(timer,&QTimer::timeout,this,&Weapon::continuToSimpleShoot);
}

void Weapon::simpleShoot()
{
    if(simpleShootReady){
        continuToSimpleShoot();
        simpleShootReady = false;
        timer->start(1000/rateOfFirePerSeconde);
    }
}

void Weapon::specialShoot(){
    if(specialShootReady){
        specialShootReady = false;
        double bulletAngleToAdd = -50;
        for(int indexBullet = 0; indexBullet < 6; indexBullet++){
            shoot(bulletAngleToAdd);
            bulletAngleToAdd += 20;
        }
        QTimer::singleShot(5000, this, &Weapon::updateSpecialShoot);
    }
}

QLineF Weapon::get_lineRotationWeapon()
{
    return lineRotationWeapon;
}

void Weapon::set_lineRotationWeapon(double argAngle){
    lineRotationWeapon.setAngle(-argAngle);
}

void Weapon::set_lineNewPositionWeapon(QPointF argPointPosWeapon){
    pointPosWeapon = argPointPosWeapon;
    lineRotationWeapon.setP1(-game->player->playerEntity->get_pointCoordOrgin() + pointPosWeapon + QPointF(img.width()/2, img.height()/2));
    lineRotationWeapon.setP2(-game->player->playerEntity->get_pointCoordOrgin() + pointPosWeapon + QPointF(0,0));
}

void Weapon::set_angleAiming(double argAngleAiming){
    angleAiming = argAngleAiming;
}

void Weapon::continuToSimpleShoot()
{
    if(game->mousePressed_.count(Qt::LeftButton)){
        shoot(0);
    }
    else {
        //if the left button is release :
        //stop shooting, stop timer, reset interval
        //and wait to shoot again
        timer->stop();
        timer->setInterval(1000/rateOfFirePerSeconde);
        QTimer::singleShot(1000/rateOfFirePerSeconde, this, &Weapon::updateSimpleShoot);
    }
}

void Weapon::updateSpecialShoot()
{
    specialShootReady = true;
}

void Weapon::updateSimpleShoot(){
    simpleShootReady = true;
}

void Weapon::shoot(double bulletAngleToAdd)
{
    double xPos = game->player->pos().x() + lineRotationWeapon.p2().x();
    double yPos = game->player->pos().y() + lineRotationWeapon.p2().y();

    Projectil * projectil = new Projectil(angleAiming + bulletAngleToAdd, xPos, yPos, 15);

    projectil->setParent(this);


    game->tabProjectil.append(projectil);

    projectil->setRotation(angleAiming + bulletAngleToAdd);
    scene()->addItem(projectil);

    connect(projectil->get_timer(),&QTimer::timeout,projectil,&Projectil::UpdatePosition);
    projectil->get_timer()->start(1000/game->fps);
}


