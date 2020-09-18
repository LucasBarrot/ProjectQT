#include "DoorToNextLevel.h"

DoorToNextLevel::DoorToNextLevel(){
    QImage img(":/Source/Source/Image/Door/doors_leaf_open.png");
    setPixmap(QPixmap::fromImage(img));
}
