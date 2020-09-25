#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Explosion : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Explosion(double argRadius);

private:
    void destroyExplosion();
};

#endif // EXPLOSION_H
