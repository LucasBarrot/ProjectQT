#ifndef ENTITYWEAPON_H
#define ENTITYWEAPON_H

#include <QGraphicsPixmapItem>

#include <QGraphicsRectItem>

//#include "Weapon.h"


class EntityWeapon : public QGraphicsPixmapItem {
public:
    //constructor
    EntityWeapon();

    //get and set
    //name weapon
    void set_nameWeapon(QString argName);
    QString get_nameWeapon();

    //damage per bullet
    void set_damage(double argDamage);
    double get_damage();

    //number of bullet per second
    void set_rateOfFire(double argRateOfFire);
    double get_rateOfFire();

    //waiting time special shoot
    void set_rateOfFireSpecial(double argTime);
    double get_rateOfFireSpecial();

    //scale image
    void set_scaleImg(double scale);
    double get_scaleImg();

    //Image weapon
    void set_imgWeapon(QString argPath);
    QImage get_imgWeapon();

    //path image Projectil
    void set_pathImgWeapon(QString argPath);
    QString get_pathImgWeapon();

    //path image Projectil
    void set_pathImgProjectil(QString argPath);
    QString get_pathImgProjectil();

    //test update pixmap
    void updatePixmap();

    //angle weapon
    void set_angleWeapon(double argAngle);
    double get_angleWeapon();

    //pos weapon
    //normal
    void set_posWeapon(QPointF argPos);
    QPointF get_posWeapon();
    //invert
    void set_posWeaponInvert(QPointF argPos);
    QPointF get_posWeaponInvert();

    //point to spawn projectil
    void set_pointSpawnProjecitl(QPointF argPoint);
    QPointF get_pointSpawnProjectil();

    //verif
    //verif special shoot
    void updateSpecialShoot(bool argReady);
    void updateSimpleShoot(bool argReady);
    bool get_specialShootReady();
    bool get_simpleShootReady();

    //invert weapon
    void turnWeapon(bool invert);

private:
    //information about weapon
    //name weapon
    QString nameWeapon;
    //number of damage per bullet
    double damage;
    //number of bulllet per second
    double rateOfFirePerSeconde;
    //how many time the spacial shoot need to be recharge
    double rateOfFireSpecial;
    //scale image
    double scaleImg;
    //Image Weapon
    QImage img;
    //path img Weapon
    QString pathImgWeapon;
    //path img projectil shoot by weapon
    QString pathImgrojectil;
    //aiming angle
    double angleAiming;
    //position Weapon Normal
    QPointF posWeapon;
    //position Weapon invert
    QPointF posWeaponInvert;
    //point to spawn projectil
    QPointF pointSpawnProjectil;

    //verif special shoot
    bool specialShootReady;
    //verif simple shoot
    bool simpleShootReady;
};

#endif // ENTITYWEAPON_H
