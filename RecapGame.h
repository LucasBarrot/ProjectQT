#ifndef RECAPGAME_H
#define RECAPGAME_H

#include <QGraphicsScene>
#include <QPushButton>

class RecapGame : public QGraphicsScene {
    Q_OBJECT
public:
    RecapGame();

    //destruction Recap
    void destructionRecap();

private slots:
    //do that when button resume is pressed
   void handleButtonGoMenu();

private:

   //resume button
    QPushButton *buttonGoMenu;
    QGraphicsProxyWidget *proxyGoMenu;


};

#endif // RECAPGAME_H
