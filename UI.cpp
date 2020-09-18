#include "UI.h"

#include "Game.h"

#include <QDebug>

extern Game* game;

UI::UI(double width, double height){
    //divide per scale
    this->setRect(0, 0, width, height);
    setBrush(Qt::blue);
    setZValue(1);



    QColor green70 = Qt::green;
    green70.setAlphaF( 0.7 );
    setBrush(green70);


    //minimap
    minimap = new Minimap(width, width);
    minimap->setParentItem(this);
}

void UI::printOnScreen(){

    //heart
    //number of heart we need to create
    int numberHeart = game->player->playerEntity->get_maxHealth() / 10;
    //size of each heart
    double sizeHeart = 10;

    //pos of heart
    double posX = 5;
    double posY = minimap->rect().height() + 10;

    //position heart in ui
    for(int indexHeart = 0; indexHeart <= numberHeart; ++indexHeart){
        if(posX + sizeHeart > rect().width() - 5) {
            posY += sizeHeart;
            posX = 5;
        }


        Heart * heart = new Heart(sizeHeart);
        heart->setPos(posX, posY);
        heart->setParentItem(this);
        tabHeart.append(heart);
        posX += sizeHeart;
    }

    //Weapon
    double size = (rect().width() - 5)/2;

    //set slot 1
    slotWeapon_1 = new SlotWeaponUI(1, size);
    slotWeapon_1->setParentItem(this);
    slotWeapon_1->setPos(5, tabHeart.at(tabHeart.size() -1)->pos().y() + sizeHeart + 5);

    //set slote 2
    slotWeapon_2 = new SlotWeaponUI(2, size);
    slotWeapon_2->setParentItem(this);
    slotWeapon_2->setPos(5 + size, tabHeart.at(tabHeart.size() -1)->pos().y() + sizeHeart + 5);

}

void UI::resize(){
    minimap->setRect(0,0, rect().width(), rect().width());
    if(tabHeart.size() != 0){


        //size one heart
        double sizeHeart = 10;

        //pos of heart
        double posX = 5;
        double posY = minimap->rect().height() + 10;

        //reposition of heart in ui
        for(int indexHeart = 0; indexHeart < tabHeart.size(); ++indexHeart){
            if(posX + sizeHeart > rect().width() - 5) {
                posY += sizeHeart;
                posX = 5;
            }

            tabHeart.at(indexHeart)->setPos(posX, posY);
            posX += sizeHeart;
        }

        //resize slot weapon
        double size = (rect().width() - 15)/2;
        //resize slot 1
        slotWeapon_1->resize(size);
        slotWeapon_1->setPos(5, tabHeart.at(tabHeart.size() -1)->pos().y() + sizeHeart + 5);

        //resize slot 2
        slotWeapon_2->resize(size);
        slotWeapon_2->setPos(5 + size, tabHeart.at(tabHeart.size() -1)->pos().y() + sizeHeart + 5);
    }

}

void UI::updateWeaponSlot(){
    //update slot weapon
    double size = (rect().width() - 15)/2;

    slotWeapon_1->updateWeaponPrint(size);
    slotWeapon_2->updateWeaponPrint(size);
}
