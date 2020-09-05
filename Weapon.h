#ifndef WEAPON_H
#define WEAPON_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QMouseEvent>

class Weapon: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT;
public:
    Weapon(double argXOriginPlayer, double argYOriginPlayer);
    void simpleShoot();
    void specialShoot();

    //line of rotation for the weapon
    QLineF get_lineRotationWeapon();
    void set_lineRotationWeapon(double argAngle);
    void set_lineNewPositionWeapon(QPointF argPointPosWeapon);
    //set the aiming angle
    void set_angleAiming(double argAngleAiming);
private:
    //number of damage per bullet
    double damage;
    //number of bulllet per second
    double rateOfFirePerSeconde;
    //how many time the spacial shoot need to be recharge
    double timeToWaitSpecialShoot;
    //verif special shoot
    bool specialShootReady;
    //verif simple shoot
    bool simpleShootReady;

    void continuToSimpleShoot();
    void updateSpecialShoot();
    void updateSimpleShoot();
    void shoot(double bulletAngleToAdd);

    void paintEvent(QPaintEvent *event);

    QMouseEvent *event;

    //timer for continuous shooting
    QTimer *timer;

    //Point where the weapon is
    QPointF pointPosWeapon;

    //Line to know where to shoot with the rotation
    QLineF lineRotationWeapon;

    //aiming angle
    double angleAiming;

    //Image Weapon
    QImage img;

};

#endif // WEAPON_H
