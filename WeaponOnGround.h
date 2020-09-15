#ifndef WEAPONONGROUND_H
#define WEAPONONGROUND_H

#include <QGraphicsPixmapItem>

#include "EntityWeapon.h"

class WeaponOnGround : public QGraphicsPixmapItem {
public:
    WeaponOnGround(EntityWeapon * argEntity);

private:
    double size;

};

#endif // WEAPONONGROUND_H
