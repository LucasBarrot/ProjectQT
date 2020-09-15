#include "Heart.h"

Heart::Heart(double argSize){
    statusHeart = 2;

    pathEmptyHeart = ":/Source/Source/Image/Heart/ui_heart_empty.png";
    pathHalfFullHeart = ":/Source/Source/Image/Heart/ui_heart_half.png";
    pathFullHeart = ":/Source/Source/Image/Heart/ui_heart_full.png";

    QImage img(pathFullHeart);
    img = img.scaled(argSize, argSize);
    setPixmap(QPixmap::fromImage(img));
}
