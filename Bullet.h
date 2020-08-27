#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QRectF>

class Bullet :  public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    explicit Bullet(QObject *parent = nullptr);

signals:

public slots:
    void move(float dx, float dy);

};

#endif // BULLET_H
