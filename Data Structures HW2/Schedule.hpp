//
//  Schedule.hpp
//  Data Structures HW2
//
//  Created by Ezzat Qupty on 05/05/2019.
//  Copyright © 2019 Ezzat Qupty. All rights reserved.
//

#ifndef Schedule_hpp
#define Schedule_hpp

#include "AVL.hpp"
#include "Linked_List.hpp"
#include "Course.hpp"
#include "Lecture_Info.hpp"


using namespace DataStructures;

class CS_system{
	LLnode<int> ** freeRooms;
	LLnode<int> *** roomsAndHours;
	AVLTree<int, course> * courses;
public:
	CS_system(int hours, int rooms){
		if(!(hours > 0 and rooms > 0))
		{//something
		}
		roomsAndHours = new LLnode<int> **[hours];
		for(int a = 0; a < hours;a++)
			roomsAndHours[a] = new LLnode<int> * [rooms];
		freeRooms = new LLnode<int>* [hours];
		for (int i = 0; i < hours; i++) {
			int m = 0;
			freeRooms[i] = new LLnode<int>(m);
			roomsAndHours[i][0] = freeRooms[i];
			LLnode<int>* parent = freeRooms[i];
			parent->setPrev(nullptr);
			for (int j = 1 ; j < rooms; j++) {
				LLnode<int>* newNode = new LLnode<int>(j);
				roomsAndHours[i][j] = newNode;
				parent->setNext(newNode);
				newNode->setPrev(parent);
				parent=newNode;
			}
		}
		courses = new AVLTree<int, course>();
	}
	void AddLecture(int hour, int roomID, int courseID){
		if(hour < 0 || roomID < 0 || courseID < 0) throw IllegalInitialization() ;
		if(!roomsAndHours[hour][roomID]){
			LLnode<int>* prevNode = roomsAndHours[hour][roomID]->getPrev();
			LLnode<int>* nextNode = roomsAndHours[hour][roomID]->getNext();
			if(!prevNode) prevNode->setNext(nextNode);
			if(!nextNode) nextNode->setPrev(prevNode);
			roomsAndHours[hour][roomID]->setPrev(nullptr);
			roomsAndHours[hour][roomID]->setNext(nullptr);
			//delete the node
		}
		if(!courses->contains(courseID)){
			course data = course(courseID);
			courses->insert(courseID, data);
		}
	}
	void GetCourseID(int hour, int roomID, int *courseID){}
	void DeleteLecture(void *DS, int hour, int roomID){}
	void ChangeCourseID(int oldCourseID, int newCourseID){}
	void CalculateScheduleEfficiency(float *efficiency){}
};

#endif /* Schedule_hpp */
