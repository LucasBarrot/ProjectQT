#include "Weapon.h"
#include "Game.h"

#include <QGraphicsScene>
#include <QDebug>

extern Game * game;

Weapon::Weapon(EntityWeapon * argEntity){
    entityWeapon = argEntity;
    setRect(0,0, entityWeapon->get_imgWeapon().width(), entityWeapon->get_imgWeapon().height());
    setTransformOriginPoint(entityWeapon->get_imgWeapon().width()/2, entityWeapon->get_imgWeapon().height()/2);

    //set position caracter
    pointPosWeapon = QPointF(16-4, 10);
    setPos(pointPosWeapon);

    test_ouputWeapon = new Collider(1,1);
    test_ouputWeapon->setPos(entityWeapon->get_imgWeapon().width(), entityWeapon->get_imgWeapon().height()/2);
    test_ouputWeapon->setParentItem(this);

    //setParent(NULL);

    entityWeapon->setParentItem(this);
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
    double xPos = test_ouputWeapon->scenePos().x();
    double yPos = test_ouputWeapon->scenePos().y();


    qDebug() <<  test_ouputWeapon->scenePos().x();

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





