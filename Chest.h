#ifndef CHEST_H
#define CHEST_H

#include <QGraphicsPixmapItem>

class Chest : public QGraphicsPixmapItem {
public:
    Chest();

    //Open Chest
    void openChest();
private:
    QString pathChestClose;
    QString pathChestOpen;
};

#endif // CHEST_H
