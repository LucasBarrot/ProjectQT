#ifndef WEAPON_H
#define WEAPON_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QMouseEvent>

class Weapon: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT;
public:
    Weapon();
    void Shoot();
private:
    double rateOfFirePerSeconde;
    void continuToShoot();

    QMouseEvent *event;

    QTimer *timer;
};

#endif // WEAPON_H
