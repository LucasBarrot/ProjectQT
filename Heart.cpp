#include "Heart.h"

Heart::Heart(double argSize){
    statusHeart = 2;

    size = argSize;

    pathEmptyHeart = ":/Source/Source/Image/Heart/ui_heart_empty.png";
    pathHalfFullHeart = ":/Source/Source/Image/Heart/ui_heart_half.png";
    pathFullHeart = ":/Source/Source/Image/Heart/ui_heart_full.png";

    QImage img(pathFullHeart);
    img = img.scaled(argSize, argSize);
    setPixmap(QPixmap::fromImage(img));
}


void Heart::updateImgHeart(int indexStatusHeart){
    //image
    QImage img;

    //if heart is empty
    if(indexStatusHeart == 0){
         img = QImage(pathEmptyHeart);
    }
    //if heart is half full
    else if(indexStatusHeart == 1){
        img = QImage(pathHalfFullHeart);
    }
    //if heart is full
    else if(indexStatusHeart == 2){
        img = QImage(pathFullHeart);
    }

    img = img.scaled(size, size);
    setPixmap(QPixmap::fromImage(img));
}
