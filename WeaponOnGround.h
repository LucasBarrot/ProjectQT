#ifndef WEAPONONGROUND_H
#define WEAPONONGROUND_H

#include <QGraphicsPixmapItem>

#include "EntityWeapon.h"

class WeaponOnGround : public QGraphicsPixmapItem {
public:
    WeaponOnGround(EntityWeapon * argEntity, double argSize);

    //get the entity of the weapon
    EntityWeapon * get_entityWeaponOnGround();

private:
    double size;

    EntityWeapon * entityWeapon;

};

#endif // WEAPONONGROUND_H
