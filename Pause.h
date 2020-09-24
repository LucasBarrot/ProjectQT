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
    //do that when button resume is pressed
   void handleButtonResume();

   //do that when button quit to menu is pressed
   void handleButtonQuitToMenu();

private:

   //resume button
    QPushButton *buttonResume;
    QGraphicsProxyWidget *proxyResume;

    //quit to menu button
    QPushButton *buttonQuitToMenu;
    QGraphicsProxyWidget *proxyQuitToMenu;
};

#endif // PAUSE_H
