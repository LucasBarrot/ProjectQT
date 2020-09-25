#include "WeaponOnGround.h"

WeaponOnGround::WeaponOnGround(EntityWeapon *argEntity, double argSize){
    //entity weapon
    entityWeapon = argEntity;

    //path to img weapon
    QString pathImgWeapon = argEntity->get_pathImgWeapon();

    QImage img(pathImgWeapon);
    double scale = argSize / img.width();
    img = img.scaled(img.width() * scale, img.height() * scale);
    setPixmap(QPixmap::fromImage(img));
}

EntityWeapon *WeaponOnGround::get_entityWeaponOnGround(){
    return entityWeapon;
}
