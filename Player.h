#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QObject>
#include <Network.h>
#include <QMouseEvent>
#include <QWidget>
class Player: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Player(Network * region);
    void keyPressEvent(QKeyEvent * event);
    void mousePressEvent( QMouseEvent *event);

private:
        double x_prev;
        double y_prev;
        Network * playable_region;
        const QRect player_rect;
public slots:
};

#endif // PLAYER_H
