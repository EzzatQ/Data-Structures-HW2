//
//  Linked List.hpp
//  Data Structures HW2
//
//  Created by Ezzat Qupty on 05/05/2019.
//  Copyright © 2019 Ezzat Qupty. All rights reserved.
//

#ifndef Linked_List_hpp
#define Linked_List_hpp

#include "Exceptions.hpp"

namespace DataStructures{
    
    template<class D>
    class LLnode{
        D* data;
        LLnode* prev;
        LLnode* next;
    public:
        LLnode(D& d): prev(nullptr), next(nullptr){
            data = new D(d);
        }
        ~LLnode(){
            delete data;
        }
        LLnode(LLnode& n){};
        LLnode& operator=(LLnode& n);
        void setPrev(LLnode* p){ prev = p; }
        void setNext(LLnode* n){ next = n; }
        LLnode* getPrev(){ return prev;  }
        LLnode* getNext(){ return next; }
        D* getData(){ return data; }
    };
    
    //////////////////////////////////////////////////////////////////////
    
    class roomBook{
        int id;
        bool booked;
    public:
        roomBook(int id):id(id), booked(false){}
        roomBook(int id, bool booked):id(id), booked(booked){}
        void setId(int newId){ id = newId; }
        void setBooked(bool newBooked){ booked = newBooked; }
        int getId(){ return id; }
        bool getBooked(){ return booked; }
    };
    
    //////////////////////////////////////////////////////////////////////
    
    
    class RH{
        int lectures;
        int hours;
        int rooms;
        int* hoursCount;
        int* roomsCount;
        LLnode<roomBook> ** freeRooms;
        LLnode<roomBook> *** roomsAndHours;
    public:
        RH(int hours, int rooms):hours(hours),rooms(rooms){
            if(!(hours > 0 and rooms > 0))
            {//something
            }
            lectures = 0;
            hoursCount = new (std::nothrow) int[hours+1];
            if(!hoursCount) throw OutOfMemory();
            roomsCount = new (std::nothrow) int[rooms+1];
            if(!roomsCount){
                delete[] hoursCount;
                throw OutOfMemory();
            }
            
            for (int i = 0; i < hours+1; i++) {
                hoursCount[i] = 0;
            }
            for (int j = 0; j < rooms+1; j++) {
                roomsCount[j] = 0;
            }
            
            roomsAndHours = new LLnode<roomBook> **[hours];
            for(int a = 0; a < hours;a++)
                roomsAndHours[a] = new LLnode<roomBook> * [rooms];
            
            
            freeRooms = new LLnode<roomBook>* [hours];
            // dont remember if i should do new...
            roomBook first =  roomBook(0);
            for (int i = 0; i < hours; i++) {
                freeRooms[i] = new LLnode<roomBook>(first);
                roomsAndHours[i][0] = freeRooms[i];
                LLnode<roomBook>* parent = freeRooms[i];
                parent->setPrev(nullptr);
                for (int j = 1 ; j < rooms; j++) {
                    roomBook second =  roomBook(j);
                    LLnode<roomBook>* newNode = new LLnode<roomBook>(second);
                    roomsAndHours[i][j] = newNode;
                    parent->setNext(newNode);
                    newNode->setPrev(parent);
                    parent=newNode;
                }
                parent->setNext(nullptr);
            }
        }
        int getHours(){ return hours; }
        int getRooms(){ return rooms; }
        bool isBooked(int hour, int room){
            return roomsAndHours[hour][room]->getData()->getBooked();
            
        }
        int getCourseAt(int hour, int room){
            if(hour < 0 || hour > hours-1 || room < 0 || room > rooms-1) throw IllegalInitialization();
            if(isBooked(hour, room))
                return roomsAndHours[hour][room]->getData()->getId();
            else return -1;
        }
        float getEfficiency(){
            if(lectures>0)
                return (float)lectures/(float)(hoursCount[hours]*roomsCount[rooms]);
            return -1;
        }
        void bookLecture(int hour, int room, int courseId){
            if(hour > hours-1 || room > rooms -1) throw IllegalInitialization();
            if(!roomsAndHours[hour][room]->getData()->getBooked()){
                lectures++;
                hoursCount[hour]++;
                roomsCount[room]++;
                if(hoursCount[hour]==1) hoursCount[hours]++;
                if(roomsCount[room]==1) roomsCount[rooms]++;
                LLnode<roomBook>* current = roomsAndHours[hour][room];
                LLnode<roomBook>* prevNode = current->getPrev();
                LLnode<roomBook>* nextNode = current->getNext();
                if(prevNode) prevNode->setNext(nextNode);
                else{
                    freeRooms[hour] = nextNode;
                }
                if(nextNode) nextNode->setPrev(prevNode);
                current->setPrev(nullptr);
                current->setNext(nullptr);
                current->getData()->setId(courseId);
                current->getData()->setBooked(true);
            }else throw AlreadyExists();
        }
        void removeLecture(int hour, int room){
            if(roomsAndHours[hour][room]->getData()->getBooked()){
                lectures--;
                hoursCount[hour]--;
                roomsCount[room]--;
                if(hoursCount[hour]==0) hoursCount[hours]--;
                if(roomsCount[room]==0) roomsCount[rooms]--;
                LLnode<roomBook>* current = roomsAndHours[hour][room];
                LLnode<roomBook>* head =freeRooms[hour];
                current->setNext(head);
                if(head) head->setPrev(current);
                freeRooms[hour] = current;
                current->getData()->setId(room);
                current->getData()->setBooked(false);
            }else throw DoesNotExist();
        }
        void getFreeRoomsAtHour(int hour, int **rooms, int* numOfRooms){
            if(hour < 0 || hour > hours-1 || !rooms || !numOfRooms) throw IllegalInitialization();
            int counter = 0;
            LLnode<roomBook> * itr = freeRooms[hour];
            while(itr && !itr->getData()->getBooked()){
                counter++;
                itr = itr->getNext();
            }
            if(counter == 0) throw DoesNotExist();
            *numOfRooms = counter;
            *rooms =(int*)malloc(sizeof(int) * (*numOfRooms));
            itr = freeRooms[hour];
            for(int i=0; i < (*numOfRooms);i++){
                (*rooms)[i] = (itr->getData()->getId());
                itr = itr->getNext();
            }
        }
        ~RH(){
            for (int i = 0; i < hours; i++) {
                LLnode<roomBook>** current = roomsAndHours[i];
                for (int j = 0 ; j < rooms; j++) {
                    delete current[j];
                }
            }
            delete[] freeRooms;
            for(int a = 0; a < hours;a++)
                delete[] roomsAndHours[a];
            delete[] roomsAndHours;
            delete[] hoursCount;
            delete[] roomsCount;
        }
        
    };

}


#endif /* Linked_List_hpp */
