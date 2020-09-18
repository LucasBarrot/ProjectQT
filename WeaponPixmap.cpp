#include "WeaponPixmap.h"


WeaponPixmap::WeaponPixmap(QString argPath, double argSizeWidth, double argSizeHeight){
    QImage img(argPath);
    img = img.scaled(argSizeWidth, argSizeHeight);
    setPixmap(QPixmap::fromImage(img));
}

void WeaponPixmap::updatePixmap(QString argPath, double argSizeWidth, double argSizeHeight){
    QImage img(argPath);
    img = img.scaled(argSizeWidth, argSizeHeight);
    setPixmap(QPixmap::fromImage(img));
}
