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
		D& data;
		LLnode* prev;
		LLnode* next;
	public:
		LLnode(D& d): data(d), prev(nullptr), next(nullptr){}
		~LLnode();
		LLnode(LLnode& n);
		LLnode& operator=(LLnode& n);
		void setPrev(LLnode* p){ prev = p; }
		void setNext(LLnode* n){ next = n; }
		LLnode* getPrev(){ return prev;  }
		LLnode* getNext(){ return next; }
        D& getData(){ return data; }
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
        int hours;
        int rooms;
        LLnode<roomBook> ** freeRooms;
        LLnode<roomBook> *** roomsAndHours;
    public:
        RH(int hours, int rooms):hours(hours),rooms(rooms){
            if(!(hours > 0 and rooms > 0))
            {//something
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
            }
        }
        int getHours(){ return hours; }
        int getRooms(){ return rooms; }
        bool isBooked(int hour, int room){
            return roomsAndHours[hour][room]->getData().getBooked();
            
        }
        int getCourseAt(int hour, int room){
            if(isBooked(hour, room))
                return roomsAndHours[hour][room]->getData().getId();
            else return -1;
        }
        void bookLecture(int hour, int room, int courseId){
            if(!roomsAndHours[hour][room]->getData().getBooked()){
                LLnode<roomBook>* current = roomsAndHours[hour][room];
                LLnode<roomBook>* prevNode = current->getPrev();
                LLnode<roomBook>* nextNode = current->getNext();
                if(!prevNode) prevNode->setNext(nextNode);
                if(!nextNode) nextNode->setPrev(prevNode);
                current->setPrev(nullptr);
                current->setNext(nullptr);
                current->getData().setId(courseId);
                current->getData().setBooked(true);
            }else throw AlreadyExists();
        }
        void removeLecture(int hour, int room){
            if(roomsAndHours[hour][room]->getData().getBooked()){
                LLnode<roomBook>* current = roomsAndHours[hour][room];
                LLnode<roomBook>* head =freeRooms[hour];
                current->setNext(head);
                head->setPrev(current);
                freeRooms[hour] = current;
                current->getData().setId(room);
                current->getData().setBooked(false);
            }else throw DoesNotExist();
        }
        void getFreeRoomsAtHour(int hour, int **rooms, int* numOfRooms){
            *numOfRooms = 0;
            LLnode<roomBook> * itr = *freeRooms[hour];
            while(itr){
                (*numOfRooms)++;
                itr = itr->getNext();
            }
            rooms = new int*[*numOfRooms];
            itr = *freeRooms[hour];
            for(int i=0; i < (*numOfRooms);i++){
                rooms[i] = new int(itr->getData().getId());
                itr = itr->getNext();
            }
        }
        ~RH(){
            for (int i = 0; i < hours; i++) {
                LLnode<roomBook>* current = freeRooms[i];
                for (int j = 1 ; j < rooms; j++) {
                    LLnode<roomBook>* next = current->getNext();
                    delete current;
                    current = next;
                }
            }
            delete freeRooms;
            for(int a = 0; a < hours;a++)
                delete roomsAndHours[a];
            delete roomsAndHours;
        }
        
    };
//    template<class D>
//    class LinkedList{
//        LLnode<D>* head;
//        int nodeCount;
//    public:
//        LinkedList(): nodeCount(0) {
//            head = new (std::nothrow) LLnode<D>(nullptr);
//            if(!head) throw OutOfMemory();
//        }
//        ~LinkedList();
//        LinkedList(LinkedList& ll);
//        LinkedList& operator=(LinkedList& ll);
//        LLnode<D>* getHead();
//        int getNodeCount();
//        void insert(D& data);
//        void contains(D& data);
//        D& getData(D& data);
//        void remove(D& data);
//        template<class Func>
//        void applyToAll(Func& f);
//    };
}


#endif /* Linked_List_hpp */
