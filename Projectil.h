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
    Projectil(double angle, double argXPos, double argYPos, double argDamage);
    //update the position every fps
    void UpdatePosition();
    //update the position on the screen
    void updatePositionOnScreen(int argIndexProjectil);

    QTimer * get_timer();
private:
    //number of damage per bullet
    double damage;

    //angle of the bullet
    double angle;

    //pos projectil
    double xPosProjectil;
    double yPosProjectil;

    //timer
    QTimer *timer;
};

#endif // PROJECTIL_H
