#ifndef UPDATE_H
#define UPDATE_H

#include <QObject>
#include <QTimer>

#include <QGraphicsItem>

#include "Game.h"

class Update: public QObject {
    Q_OBJECT;
public:
    Update(double fps);
private:
    void updateBaseOnFps();
    double fps;
    int indexFps;
    //verif if it is the first frame
    bool firstFrame;
};

#endif // UPDATE_H
