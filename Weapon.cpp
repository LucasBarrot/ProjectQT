#include "Weapon.h"
#include "Game.h"

extern Game * game;

Weapon::Weapon()
{
    QImage img(":/Source/Source/Image/Weapon/weapon_red_magic_staff.png");
    img = img.scaled(4, 10);
    setPixmap(QPixmap::fromImage(img));
    setTransformOriginPoint(img.width()/2, img.height()/2);
}

void Weapon::Shoot()
{

}
