#ifndef UPDATE_H
#define UPDATE_H

#include <QObject>
#include <QTimer>

#include <QGraphicsItem>

#include "Game.h"

class Update: public QObject, public QGraphicsRectItem {
    Q_OBJECT;
public:
    Update(double fps, QTimer * argTimer);
    QTimer * timer;
private:
    void updateBaseOnFps();
    double fps;
    int indexFps;
    //verif if it is the first frame
    bool firstFrame;
};

#endif // UPDATE_H
