#include "Projectil.h"

#include <qmath.h> // qSin, qCos, qTan


Projectil::Projectil()
{
    QImage img(":/Source/Source/Image/projectil/Projectil_1.png");
    setPixmap(QPixmap::fromImage(img));
    setTransformOriginPoint(img.width()/2, img.height()/2);
}

void Projectil::moveProjectil()
{
    int STEP_SIZE = 30;
    double theta = rotation(); // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);


}
