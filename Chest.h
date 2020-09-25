#ifndef CHEST_H
#define CHEST_H

#include <QGraphicsPixmapItem>

class Chest : public QGraphicsPixmapItem {
public:
    Chest();

    //get chest open
    bool get_chestOpen();

    //Open Chest
    void openChest();
private:
    //verif chest open
    bool chestOpen;

    //path to chest img
    QString pathChestClose;
    QString pathChestOpen;
};

#endif // CHEST_H
