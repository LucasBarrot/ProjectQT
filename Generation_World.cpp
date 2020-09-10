#include "Generation_World.h"


//#include <QGraphicsScene>
#include <stdlib.h>
#include <QDebug>
#include <random>
#include <time.h>


Generation_World::Generation_World(){
    srand(time(NULL));
    numberRoom = rand()%(numberRoomHigh-numberRoomLow + 1) + numberRoomLow;
    qDebug() << "Number Room : " << numberRoom;

    heightWall = 16;
    heightBridge = 16 * 5;
}

void Generation_World::generate()
{
    //position : 0 = top, 1 = right, 2 = bottom, 3 = left

    //create the first room
    Room * firstRoom = new Room(heightWall, heightBridge);
    tabRoomFree.append(firstRoom);
    tabRoom.append(firstRoom);
    scene()->addItem(tabRoomFree.at(0));
    // Argument "-1" because no other room
    tabRoomFree.at(0)->constructor(-1, "spawn");
    tabRoomFree.at(0)->setTransformOriginPoint(tabRoomFree.at(0)->get_height()/2,tabRoomFree.at(0)->get_width()/2);

    int spaceXBetweenRoom = 16 * 25;
    int spaceYBetweenRoom = 16 * 25;

    int next_coord_x, next_coord_y;

    //create group of collider to detect side room
    Collider * colliderTop = new Collider(200, 200);
    colliderTop->setPos(0, -300);
    Collider * colliderRight = new Collider(200, 200);
    colliderRight->setPos(300, 0);
    Collider * colliderBottom = new Collider(200, 200);
    colliderBottom->setPos(0, 300);
    Collider * colliderLeft = new Collider(200, 200);
    colliderLeft->setPos(-300, 0);

    scene()->addItem(colliderTop);
    scene()->addItem(colliderRight);
    scene()->addItem(colliderBottom);
    scene()->addItem(colliderLeft);

    int checkNumberBridge = 0;

    bool verif;

    //set-up variable to check the number of room
    int indexRoom = 1;
    int CheckRoom = 1;
    //set up variable to check the number of gift room
    int checkNGiftRoom = 0;
    // Create all room and bridge
    while(CheckRoom < numberRoom){
        verif = false;
        int nSideRoom = 0;
        // set a random index in tabRoomFree
        int indexRoomRandom = 0;
        if(indexRoom != 1){
            indexRoomRandom = rand()%(tabRoomFree.size());
        }

        colliderTop->setPos(tabRoomFree.at(indexRoomRandom)->group->x() + 0, tabRoomFree.at(indexRoomRandom)->group->y() - spaceYBetweenRoom);
        colliderRight->setPos(tabRoomFree.at(indexRoomRandom)->group->x() + spaceXBetweenRoom, tabRoomFree.at(indexRoomRandom)->group->y() + 0);
        colliderBottom->setPos(tabRoomFree.at(indexRoomRandom)->group->x() + 0, tabRoomFree.at(indexRoomRandom)->group->y() + spaceYBetweenRoom);
        colliderLeft->setPos(tabRoomFree.at(indexRoomRandom)->group->x() - spaceXBetweenRoom, tabRoomFree.at(indexRoomRandom)->group->y() + 0);

        QList<QGraphicsItem *> colliding_items_Top = colliderTop->collidingItems();
        QList<QGraphicsItem *> colliding_items_Right = colliderRight->collidingItems();
        QList<QGraphicsItem *> colliding_items_Bottom = colliderBottom->collidingItems();
        QList<QGraphicsItem *> colliding_items_Left = colliderLeft->collidingItems();

        bool verifRoomTop = false;
        bool verifRoomRight = false;
        bool verifRoomBottom = false;
        bool verifRoomLeft = false;

        verifRoomTop = verifCollider(colliding_items_Top);
        verifRoomRight = verifCollider(colliding_items_Right);
        verifRoomBottom = verifCollider(colliding_items_Bottom);
        verifRoomLeft = verifCollider(colliding_items_Left);

        if(verifRoomTop == true){
            nSideRoom ++;
        }

        if(verifRoomRight == true){
            nSideRoom ++;
        }

        if(verifRoomBottom == true){
            nSideRoom ++;
        }

        if(verifRoomLeft == true){
            nSideRoom ++;
        }

        if(nSideRoom != 4){

            int WichSideToAddRoom = rand() % (4 - nSideRoom);

            //Check where the next room need to be
            for(int indexSide = 0; indexSide < 4; indexSide++){
                if(verifRoomTop == true && WichSideToAddRoom == 0){
                    WichSideToAddRoom ++;
                }
                else if(verifRoomTop == false && WichSideToAddRoom == 0){
                    next_coord_x = 0;
                    next_coord_y = -spaceYBetweenRoom;
                    verif = true;
                    break;
                }

                else if(verifRoomRight == true && WichSideToAddRoom == 1){
                    WichSideToAddRoom ++;
                }
                else if(verifRoomRight == false && WichSideToAddRoom == 1){
                    next_coord_x = +spaceXBetweenRoom;
                    next_coord_y = 0;
                    verif = true;
                    break;
                }

                if(verifRoomBottom == true && WichSideToAddRoom == 2){
                    WichSideToAddRoom ++;
                }
                else if(verifRoomBottom == false && WichSideToAddRoom == 2){
                    next_coord_x = 0;
                    next_coord_y = spaceYBetweenRoom;
                    verif = true;
                    break;
                }

                if(verifRoomLeft == true && WichSideToAddRoom == 3){
                    WichSideToAddRoom ++;
                }
                else if(verifRoomLeft == false && WichSideToAddRoom == 3){
                    next_coord_x = -spaceXBetweenRoom;
                    next_coord_y = 0;
                    verif = true;
                    break;
                }

                if(WichSideToAddRoom > 3){
                    WichSideToAddRoom = 0;
                }
            }

            int SidePreviousRoom;
            if(WichSideToAddRoom - 2 < 0){
                SidePreviousRoom = WichSideToAddRoom + 2;
            }
            else {
                SidePreviousRoom = WichSideToAddRoom - 2;
            }

            //Create room
            Room * new_room = new Room(heightWall, heightBridge);
            tabRoomFree.push_back(new_room);
            tabRoom.push_back(new_room);

            scene()->addItem(tabRoomFree.at(indexRoom));

            int randomTypeRoom = rand() % 4;

            bool verifGiftRoom = false;

            double xOriginsRandomRoom = tabRoomFree.at(indexRoomRandom)->group->x() +  tabRoomFree.at(indexRoomRandom)->transformOriginPoint().x() ;
            double yOriginsRandomRoom = tabRoomFree.at(indexRoomRandom)->group->y() +  tabRoomFree.at(indexRoomRandom)->transformOriginPoint().y() ;

            if(randomTypeRoom == 3 && checkNGiftRoom < 2){
                tabRoomFree.at(indexRoom)->constructor(SidePreviousRoom, "giftRoom");
                verifGiftRoom = true;
                checkNGiftRoom ++;   }
            else if(CheckRoom == numberRoom -1){
                tabRoomFree.at(indexRoom)->constructor(SidePreviousRoom, "bossRoom");
            }
            else {
                tabRoomFree.at(indexRoom)->constructor(SidePreviousRoom, "monsterRoom");
            }

            tabRoomFree.at(indexRoom)->setTransformOriginPoint(tabRoomFree.at(indexRoom)->get_width()/2,tabRoomFree.at(indexRoom)->get_height()/2);
            qDebug() << tabRoomFree.at(indexRoom)->transformOriginPoint();

            qDebug() << "Room n°" << indexRoomRandom << " : x() : " <<xOriginsRandomRoom << ", y() : " << yOriginsRandomRoom;

            tabRoomFree.at(indexRoomRandom)->update_side_gate(WichSideToAddRoom, tabRoomFree.at(indexRoomRandom)->group->x(), tabRoomFree.at(indexRoomRandom)->group->y());
            tabRoomFree.at(indexRoom)->group->setPos(xOriginsRandomRoom  + next_coord_x - tabRoomFree.at(indexRoom)->transformOriginPoint().x(), yOriginsRandomRoom + next_coord_y - tabRoomFree.at(indexRoom)->transformOriginPoint().y());
            tabRoomFree.at(indexRoom)->setPos(xOriginsRandomRoom  + next_coord_x - tabRoomFree.at(indexRoom)->transformOriginPoint().x(), yOriginsRandomRoom + next_coord_y - tabRoomFree.at(indexRoom)->transformOriginPoint().y());
            qDebug() << "Room created n°" << indexRoom << " : x() : " <<xOriginsRandomRoom  + next_coord_x  - tabRoomFree.at(indexRoom)->transformOriginPoint().x() << ", y() : " << yOriginsRandomRoom + next_coord_y - tabRoomFree.at(indexRoom)->transformOriginPoint().y();
            tabRoomFree.at(indexRoom)->set_ifRoom(SidePreviousRoom);
            tabRoomFree.at(indexRoomRandom)->set_ifRoom(WichSideToAddRoom);

            int lenghtBetweenTwoRoomX = spaceXBetweenRoom - tabRoomFree.at(indexRoomRandom)->get_width()/2 - tabRoomFree.at(indexRoom)->get_width()/2;
            int lenghtBetweenTwoRoomY = spaceYBetweenRoom - tabRoomFree.at(indexRoomRandom)->get_height()/2 - tabRoomFree.at(indexRoom)->get_height()/2;

            //Create bridge
            Bridge * new_bridge = new Bridge(heightWall, heightBridge);
            tab_bridge.push_back(new_bridge);

            if(WichSideToAddRoom == 0){
                checkNumberBridge = addBridge(WichSideToAddRoom, checkNumberBridge, indexRoomRandom, tabRoomFree.at(indexRoomRandom)->get_height()/2 - tab_bridge.at(checkNumberBridge)->get_width() / 2, -lenghtBetweenTwoRoomY ,lenghtBetweenTwoRoomY);
            }
            if(WichSideToAddRoom == 1){
                checkNumberBridge = addBridge(WichSideToAddRoom, checkNumberBridge, indexRoomRandom, tabRoomFree.at(indexRoomRandom)->get_width(),  (tabRoomFree.at(indexRoomRandom)->get_height() - tab_bridge.at(checkNumberBridge)->get_width())/2,lenghtBetweenTwoRoomX);
//                tab_bridge.at(checkNumberBridge - 1)->group->setRotation(-90);
            }
            if(WichSideToAddRoom == 2){
                checkNumberBridge = addBridge(WichSideToAddRoom, checkNumberBridge, indexRoomRandom, tabRoomFree.at(indexRoomRandom)->get_height()/2 - tab_bridge.at(checkNumberBridge)->get_width() / 2, tabRoomFree.at(indexRoomRandom)->get_height(),lenghtBetweenTwoRoomY);
            }
            if(WichSideToAddRoom == 3)
            {
                checkNumberBridge = addBridge(WichSideToAddRoom, checkNumberBridge, indexRoomRandom, -lenghtBetweenTwoRoomX, tabRoomFree.at(indexRoomRandom)->get_height()/2 - tab_bridge.at(checkNumberBridge)->get_width() / 2, lenghtBetweenTwoRoomX);
//                tab_bridge.at(checkNumberBridge - 1)->group->setRotation(90);
            }



            if (verifGiftRoom == true){
                tabRoomFree.remove(indexRoom);
                indexRoom --;
            }
            if(nSideRoom == 3){
                tabRoomFree.remove(indexRoomRandom + 1);
                indexRoom --;
            }

            CheckRoom ++;
            indexRoom ++;
        }
        else {
            tabRoomFree.remove(indexRoomRandom);
            indexRoom --;
        }


    }

    qDebug() << CheckRoom;
    qDebug() << checkNumberBridge;
}

double Generation_World::get_heightWall()
{
    return heightWall;
}


int Generation_World::addBridge(int nSide, int checkNumberBridge, int nRoomRandom, int xdisplacement, int yDisplacement, int height){
    scene()->addItem(tab_bridge.at(checkNumberBridge));
    tab_bridge.at(checkNumberBridge)->ConstructBridge(height, nSide);
    tab_bridge.at(checkNumberBridge)->group->setPos(tabRoomFree.at(nRoomRandom)->group->x() + xdisplacement, tabRoomFree.at(nRoomRandom)->group->y() + yDisplacement);
    checkNumberBridge ++;
    return checkNumberBridge;
}

bool Generation_World::verifCollider(QList<QGraphicsItem *> list_Collider)
{
    for (int i = 0, n = list_Collider.size(); i < n; ++i){
         if (typeid(*(list_Collider[i])) == typeid(Ground)){
            return true;
         }
    }
    return false;
}



