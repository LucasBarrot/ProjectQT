#ifndef HEART_H
#define HEART_H

#include <QGraphicsPixmapItem>

class Heart : public QGraphicsPixmapItem {
public :
    Heart(double argSize);

    //change image heart
    void updateImgHeart(int indexStatusHeart);
private:
    //heart status
    // 0 : empty
    // 1 : half full
    // 2 : full
    int statusHeart;

    //heart image status
    QString pathEmptyHeart;
    QString pathHalfFullHeart;
    QString pathFullHeart;

    //size
    double size;
};

#endif // HEART_H
