#ifndef WEAPON_H
#define WEAPON_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QMouseEvent>

#include "EntityWeapon.h"

class Weapon: public QObject, public QGraphicsRectItem{
    Q_OBJECT;
public:
    Weapon(double argXOriginPlayer, double argYOriginPlayer);
    //click left button
    void simpleShoot();
    //click right button
    void specialShoot();

    EntityWeapon * entityWeapon;


private:

    //set wizard staff
    EntityWeapon * set_wizardStaff();


    void continuToSimpleShoot();

    void shoot(double bulletAngleToAdd);

    void paintEvent(QPaintEvent *event);

    QMouseEvent *event;

    void updateSpecialShoot();

    //timer for continuous shooting
    QTimer *timer;

    //Point where the weapon is
    QPointF pointPosWeapon;

};

#endif // WEAPON_H
