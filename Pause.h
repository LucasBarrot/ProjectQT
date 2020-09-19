#ifndef PAUSE_H
#define PAUSE_H

#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsProxyWidget>

class Pause : public QGraphicsScene {
    Q_OBJECT
public:
    Pause();

    //destruction pause
    void destructionPause();

private slots:
   void handleButtonResume();

private:

    QPushButton *buttonResume;

    QGraphicsProxyWidget *proxy;
};

#endif // PAUSE_H
