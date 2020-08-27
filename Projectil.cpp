#include "Projectil.h"
#include "Game.h"

#include <qmath.h> // qSin, qCos, qTan
#include <QGraphicsScene>

extern Game * game;

Projectil::Projectil()
{
    QImage img(":/Source/Source/Image/projectil/Projectil_1.png");
    setPixmap(QPixmap::fromImage(img));
    setTransformOriginPoint(img.width()/2, img.height()/2);
}

void Projectil::moveProjectil()
{
    int STEP_SIZE = 10;
    double theta = rotation(); // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

    QList<QGraphicsItem *> colliding_items = collidingItems();

    bool verifWall = false;
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
         if (typeid(*(colliding_items[i])) == typeid(Wall)){
            verifWall = true;
            break;
         }
    }

    if(verifWall){
        game->tabProjectil.removeOne(this);
        scene()->removeItem(this);
        delete this;
    }


}
