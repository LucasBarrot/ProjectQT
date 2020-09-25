#include "Potion.h"

Potion::Potion(){
    healthEarn = 20;

    QImage img(":/Source/Source/Image/Potion/flask_big_red.png");
    setPixmap(QPixmap::fromImage(img));
}

double Potion::get_healtEarn(){
    return healthEarn;
}
