#ifndef MENU_H
#define MENU_H

#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsProxyWidget>



class Menu : public QGraphicsScene {
    Q_OBJECT
public:
    Menu();

    void destructionMenu();
private slots:
   void handleButtonLaunchGame();

private:

    QPushButton *buttonLaunchGame;

    QGraphicsProxyWidget *proxy;
};

#endif // MENU_H
