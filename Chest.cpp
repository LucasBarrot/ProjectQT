#include "Chest.h"

Chest::Chest(){
    pathChestClose = ":/Source/Source/Image/Chest/chest_full_open_anim_f0.png";
    pathChestOpen = ":/Source/Source/Image/Chest/chest_full_open_anim_f2.png";

    QImage img(pathChestClose);
    setPixmap(QPixmap::fromImage(img));
}

void Chest::openChest(){
    QImage img(pathChestOpen);
    setPixmap(QPixmap::fromImage(img));


}
