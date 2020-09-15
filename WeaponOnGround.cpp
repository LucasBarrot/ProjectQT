#include "WeaponOnGround.h"

WeaponOnGround::WeaponOnGround(EntityWeapon *argEntity){

    //size weapon
    size = 12;

    //path to img weapon
    QString pathImgWeapon = argEntity->get_pathImgWeapon();

    QImage img(pathImgWeapon);
    img = img.scaled(size, size);
    setPixmap(QPixmap::fromImage(img));
}
