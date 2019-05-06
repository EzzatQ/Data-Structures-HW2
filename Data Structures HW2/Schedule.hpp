//
//  Schedule.hpp
//  Data Structures HW2
//
//  Created by Ezzat Qupty on 05/05/2019.*
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
    RH * timeTable;
	AVLTree<int, course> * courses;
public:
	CS_system(int hours, int rooms){
        timeTable = new RH(hours, rooms);
        courses = new AVLTree<int, course>();
	}
	void AddLecture(int hour, int roomID, int courseID){
        timeTable->bookLecture(hour, roomID, courseID);
        //checking if the course exists or not, if does then we:
        //adding the lecture to the course`s tree by a function
        //if not we add it then we do the prev step
	}
	void GetCourseID(int hour, int roomID, int *courseID){
        *courseID = timeTable->getCourseAt(hour, roomID);
    }
	void DeleteLecture(void *DS, int hour, int roomID){
        timeTable->removeLecture(hour, roomID);
        //removing from the tree and if its an empty tree then removing the course
    }
	void ChangeCourseID(int oldCourseID, int newCourseID){
        try{
            course currNode = courses->getData(newCourseID);
        
        }catch(DoesNotExist a){
            //course newData = new course(courses->getData(oldCourseID));
            
        }
        
    }
	void CalculateScheduleEfficiency(float *efficiency){}
    void GetAllFreeRoomsByHour(int hour, int **rooms, int* numOfRooms){}
    void GetAllLecturesByCourse(int courseID, int **hours, int **rooms, int *numOfLectures){}
    ~CS_system(){
        delete timeTable;
        delete courses;
    }
};

#endif /* Schedule_hpp */
