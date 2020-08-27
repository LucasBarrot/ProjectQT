#ifndef WEAPON_H
#define WEAPON_H

#include <QGraphicsPixmapItem>

class Weapon: public QGraphicsPixmapItem{
public:
    Weapon();
    void Shoot();
};

#endif // WEAPON_H
