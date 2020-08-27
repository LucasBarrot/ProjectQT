#include "Collider.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>

Collider::Collider(double xSize, double ySize)
{
    setRect(0, 0, xSize, ySize);
    setVisible(false);

}
