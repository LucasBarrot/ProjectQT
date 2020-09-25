#ifndef PROJECTIL_H
#define PROJECTIL_H

#include <QGraphicsPixmapItem>
#include <QTime>
#include <time.h>
#include <QObject>

#include "Wall.h"
#include "Enemy.h"

class Projectil: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Projectil(double angle,
              double argXPos,
              double argYPos,
              double argDamage,
              QString argPhathImageProjectil,
              double argDisplacement);

    //set explosion
    void set_explosion(double argRadius);

    //update the position every fps
    void UpdatePosition();
    //update the position on the screen
    void updatePositionOnScreen(int argIndexProjectil);

    //set and get parent name
    void set_parentName(QString argParentName);
    QString get_parentName();

    //QTimer
    QTimer * get_timer();

    //destruciton projectil
    void destructionProjectil();

private:
    //number of damage per bullet
    double damage;

    //angle of the bullet
    double angle;

    //parent name
    QString parentName;

    //pos projectil
    double xPosProjectil;
    double yPosProjectil;

    //timer
    QTimer *timer;

    //displacement projectil
    double displacement;

    //if explosion append when projectil touch something
    bool verifExplosion;

    //parameter explosion
    //radius
    double radius;
};

#endif // PROJECTIL_H
