//
//  CS_system.cpp
//  Data Structures HW2
//
//  Created by Hasan Egbarie on 03/05/2019.
//  Copyright © 2019 Ezzat Qupty. All rights reserved.
//

#include "library.h"
#include "AVL.hpp"
#include "courseData.hpp"
using namespace DataStructures;
class Cnode{
    int data;
    Cnode* prev;
    Cnode* next;
public:
    Cnode(int d):data(d){};
    void setPrev(Cnode* p){ prev = p; };
    void setNext(Cnode* n){ next = n; };
};
class CS_system{
    Cnode * freeRooms;
    Cnode * roomsAndHours;
    AVLTree<int, course> * courses;
public:
    
};
void *Init(int hours, int rooms){
    Cnode * freeRooms[hours];
    for (int i = 0; i < hours; i++) {
        freeRooms[i] = new Cnode(0);
        Cnode* parent= freeRooms[i];
        for (int j = 1 ; j < rooms; j++) {
            Cnode* newNode = new Cnode(j);
            parent->setNext(newNode);
            newNode->setPrev(parent);
            parent=newNode;
        }
    }
    
}
