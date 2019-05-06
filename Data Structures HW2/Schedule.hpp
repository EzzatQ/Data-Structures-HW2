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
            AVLTree<DataStructures::LectureInfo, int>* currTree = courses->getData(newCourseID).getScheduled();
            AVLTree<DataStructures::LectureInfo, int>* prevTree = courses->getData(oldCourseID).getScheduled();
            int m = currTree->getNodeCount();
            int n = prevTree->getNodeCount();
            node<DataStructures::LectureInfo, int> ** array1 = new node<DataStructures::LectureInfo, int> *[m];
            node<DataStructures::LectureInfo, int> ** array2 = new node<DataStructures::LectureInfo, int> *[n];
            node<DataStructures::LectureInfo, int> ** array3 = new node<DataStructures::LectureInfo, int> *[m+n];
            currTree->fillAnArray(array1);
            prevTree->fillAnArray(array2);
            node<DataStructures::LectureInfo, int> ** p1 = array1;
            node<DataStructures::LectureInfo, int> ** p2 = array2;
            for(int i=0; i < m+n; i++){
                if((*p1)->getKey()<(*p2)->getKey()){
                    array3[i] = *p1;
                    p1++;
                }else{
                    array3[i] = *p2;
                    p2++;
                }
            }
            delete[] array1;
            delete[] array2;
            AVLTree<DataStructures::LectureInfo, int>* newTree = treeFill(array3, m+n);
            courses->remove(oldCourseID);
            courses->getData(newCourseID).setScheduled(newTree);
        }catch(DoesNotExist a){
            course* newData = new course(courses->getData(oldCourseID));
            newData->setCourseID(newCourseID);
            courses->insert(newCourseID, *newData);
            courses->remove(oldCourseID);
        }
    }
    ///////////////// filling a tree should be moved i think
    void treeFill_aux(node<DataStructures::LectureInfo, int> * root,node<DataStructures::LectureInfo, int> ** array,int start,int finish){
        int middle = (finish - start)/2;
        if(middle-start!=0){
            root->setLeft(array[start+(middle-start)/2]);
            treeFill_aux(root->getLeft(),array,start,middle);
        }
        if(finish-middle!=0){
            root->setRight(array[middle+(finish-middle)/2]);
            treeFill_aux(root->getRight(),array,middle,finish);
        }
    }
    AVLTree<DataStructures::LectureInfo, int>* treeFill(node<DataStructures::LectureInfo, int> ** array, int m){
        node<DataStructures::LectureInfo, int> *root = array[m/2];
        treeFill_aux(root, array, 0, m-1);
        return new AVLTree<DataStructures::LectureInfo, int>(root,m);
    }
    ////////////
	void CalculateScheduleEfficiency(float *efficiency){}
    void GetAllFreeRoomsByHour(int hour, int **rooms, int* numOfRooms){}
    void GetAllLecturesByCourse(int courseID, int **hours, int **rooms, int *numOfLectures){}
    ~CS_system(){
        delete timeTable;
        delete courses;
    }
};

#endif /* Schedule_hpp */
