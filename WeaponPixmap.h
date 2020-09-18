#ifndef WEAPONPIXMAP_H
#define WEAPONPIXMAP_H

#include <QGraphicsPixmapItem>

class WeaponPixmap : public QGraphicsPixmapItem {
public :
    WeaponPixmap(QString argPath, double argSizeWidth, double argSizeHeight);

    void updatePixmap(QString argPath, double argSizeWidth, double argSizeHeight);
private:

};

#endif // WEAPONPIXMAP_H
