#ifndef WEAPON_H
#define WEAPON_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QMouseEvent>

#include "EntityWeapon.h"
#include "Collider.h"
#include "WeaponPixmap.h"


class Weapon: public QObject, public QGraphicsRectItem{
    Q_OBJECT;
public:
    Weapon();

    //Call after constructeur
    void callAfter(EntityWeapon * argEntity);

    //click left button call attack_1 weapon
    void simpleShoot();

    //click right button call attack_2 weapon
    void specialShoot();

    EntityWeapon * entityWeapon;

    Collider * test_ouputWeapon;

    //update pixmap after changing weapon
    void updatePixmap();

    //weapon equip change
    void weaponEquipeChange();

    //update verif true to shoot again
    void updateSpecialShoot();

    //set and get attack
    //attack 1
    void set_attack_1(void (Weapon::*ptr)(double));
    void doAttack_1(double argAngle);
    //attack 2
    void set_attack_2(void (Weapon::*ptr)());
    void doAttack_2();


    //list of attack
    //simple
    void oneShoot(double bulletAngleToAdd);

    //special
    void arcShoot();


private:
    void continuToSimpleShoot();

    void paintEvent(QPaintEvent *event);

    QMouseEvent *event;

    //timer for continuous shooting
    QTimer *timerSimpleShoot;
    QTimer *timerSpecialShoot;

    //Point where the weapon is
    QPointF pointPosWeapon;

    //weapon pixmap
    WeaponPixmap * weaponPixmap;

    //set attack weapon
    //attack 1 : continuous shoot
    void (Weapon::*attack_1)(double);
    //attack 2 : special shoot
    void (Weapon::*attack_2)();

};

#endif // WEAPON_H
