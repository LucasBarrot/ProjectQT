#ifndef POTION_H
#define POTION_H

#include <QGraphicsPixmapItem>

class Potion : public QGraphicsPixmapItem {
public:
    Potion();

    //get health earn by the potion
    double get_healtEarn();

private:
    double healthEarn;
};

#endif // POTION_H
