#include "Weapon.h"
#include "Game.h"

#include <QGraphicsScene>
#include <QDebug>

extern Game * game;

Weapon::Weapon(double argXOriginPlayer, double argYOriginPlayer){

    entityWeapon = set_wizardStaff();

    setRect(0,0, entityWeapon->get_imgWeapon().width(), entityWeapon->get_imgWeapon().height());
    setTransformOriginPoint(entityWeapon->get_imgWeapon().width()/2, entityWeapon->get_imgWeapon().height()/2);

    //set position caracter
    pointPosWeapon = QPointF(16-4, 10);
    setPos(pointPosWeapon);

    entityWeapon->set_linePos(QPointF(-QPointF(argXOriginPlayer, argYOriginPlayer) + pointPosWeapon + QPointF(entityWeapon->get_imgWeapon().width()/2, entityWeapon->get_imgWeapon().height()/2)), QPointF(-QPointF(argXOriginPlayer, argYOriginPlayer) + pointPosWeapon));

    setParent(NULL);
}

void Weapon::simpleShoot()
{
    if(entityWeapon->get_simpleShootReady() && game->mousePressed_.count(Qt::LeftButton)){
        shoot(0);
        entityWeapon->updateSimpleShoot(false);
        QTimer::singleShot(1000/entityWeapon->get_rateOfFire(), this, &Weapon::continuToSimpleShoot);
    }
}

void Weapon::continuToSimpleShoot(){

        entityWeapon->updateSimpleShoot(true);
        simpleShoot();
}

void Weapon::updateSpecialShoot(){
    entityWeapon->updateSpecialShoot(true);
}

//shoot simple and special
void Weapon::shoot(double bulletAngleToAdd){
    double xPos = game->player->pos().x() + entityWeapon->get_lineRotationWeapon().p2().x();
    double yPos = game->player->pos().y() + entityWeapon->get_lineRotationWeapon().p2().y();

    Projectil * projectil = new Projectil(entityWeapon->get_angleWeapon() + bulletAngleToAdd, xPos, yPos, 15, entityWeapon->get_pathImgProjectil() /*modify when entity weapon done*/);

    projectil->setParent(this);

    projectil->set_parentName(typeid (Player).name());

    game->tabProjectil.append(projectil);

    projectil->setRotation(entityWeapon->get_angleWeapon() + bulletAngleToAdd);
    scene()->addItem(projectil);

    connect(projectil->get_timer(),&QTimer::timeout,projectil,&Projectil::UpdatePosition);
    projectil->get_timer()->start(1000/game->fps);
}

void Weapon::specialShoot(){
    if(entityWeapon->get_specialShootReady()){
        entityWeapon->updateSpecialShoot(false);
        double bulletAngleToAdd = -50;
        for(int indexBullet = 0; indexBullet < 6; indexBullet++){
            shoot(bulletAngleToAdd);
            bulletAngleToAdd += 20;
        }
        QTimer::singleShot(5000, this, &Weapon::updateSpecialShoot);
    }
}

EntityWeapon * Weapon::set_wizardStaff(){
    EntityWeapon * tmpEntity = new EntityWeapon();

    tmpEntity->setParentItem(this);

    //set name weapon
    tmpEntity->set_nameWeapon("Wizard_Staff");

    //set damage per bullet of the weapon
    tmpEntity->set_damage(15);

    //set rate Of Fire simple shoot per second
    tmpEntity->set_rateOfFire(2);

    //set rate of fire special shoot in second
    tmpEntity->set_rateOfFireSpecial(5);

    //set img weapon
    tmpEntity->set_imgWeapon(":/Source/Source/Image/Weapon/weapon_red_magic_staff.png");

    //set img projectil shoot by weapon
    tmpEntity->set_pathImgProjectil(":/Source/Source/Image/projectil/Projectil_1.png");

    //angle aiming (obsolete)
    tmpEntity->set_angleWeapon(0);

    //set pos weapon
    tmpEntity->set_posWeapon(QPointF(12,10));
    tmpEntity->set_posWeaponInvert(QPointF(0, 10));

    return tmpEntity;
}



