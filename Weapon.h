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
    Weapon(EntityWeapon * argEntity);
    //click left button
    void simpleShoot();
    //click right button
    void specialShoot();

    EntityWeapon * entityWeapon;

    Collider * test_ouputWeapon;

    //update pixmap after changing weapon
    void updatePixmap();

    //weapon equip change
    void weaponEquipeChange();


private:

    void continuToSimpleShoot();

    void shoot(double bulletAngleToAdd);

    void paintEvent(QPaintEvent *event);

    QMouseEvent *event;

    void updateSpecialShoot();

    //timer for continuous shooting
    QTimer *timerSimpleShoot;
    QTimer *timerSpecialShoot;

    //Point where the weapon is
    QPointF pointPosWeapon;

    //weapon pixmap
    WeaponPixmap * weaponPixmap;

};

#endif // WEAPON_H
