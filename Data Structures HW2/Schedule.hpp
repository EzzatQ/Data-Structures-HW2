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
        if(hours < 1 || rooms < 1) throw IllegalInitialization();
        timeTable = new RH(hours, rooms);
        courses = new AVLTree<int, course>();
	}
	void AddLecture(int hour, int roomID, int courseID){
        if(hour < 0 || roomID < 0 || courseID < 1) throw IllegalInitialization();
        timeTable->bookLecture(hour, roomID, courseID);
        try{
            course *a = &(courses->getData(courseID));
            a->addLecture(hour, roomID);
        }catch(...){// should specify the exception
            course *newCourse = new course(courseID);
            courses->insert(courseID, *newCourse);
            delete newCourse;
            course *b = &(courses->getData(courseID));
            b->addLecture(hour, roomID);
        }
	}
	void GetCourseID(int hour, int roomID, int *courseID){
        if(hour < 0 || roomID < 0) throw IllegalInitialization();
        *courseID = timeTable->getCourseAt(hour, roomID);
    }
	void DeleteLecture(int hour, int roomID){
        //check for exceptions, and if this even works
        if(hour < 0 || roomID < 0) throw IllegalInitialization();
        int *courseID = new int(0);
        GetCourseID(hour, roomID, courseID);
        timeTable->removeLecture(hour, roomID);
        courses->getData(*courseID).removeLecture(hour, roomID);
        if(courses->getData(*courseID).getLecNum()==0)
            courses->remove(*courseID);
        delete courseID;
    }
    
    
    
	void ChangeCourseID(int oldCourseID, int newCourseID){
        if(oldCourseID < 1 || newCourseID < 1) throw IllegalInitialization();
        if(oldCourseID == newCourseID) return;
        try{
            AVLTree<DataStructures::LectureInfo, int>* prevTree = courses->getData(oldCourseID).getScheduled();
            AVLTree<DataStructures::LectureInfo, int>* currTree = courses->getData(newCourseID).getScheduled();
            int m = currTree->getNodeCount();
            int n = prevTree->getNodeCount();
            node<DataStructures::LectureInfo, int> ** array1 = new node<DataStructures::LectureInfo, int> *[m];
            node<DataStructures::LectureInfo, int> ** array2 = new node<DataStructures::LectureInfo, int> *[n];
            node<DataStructures::LectureInfo, int> ** array3 = new node<DataStructures::LectureInfo, int> *[m+n];
            currTree->fillAnArray(array1);
            prevTree->fillAnArray(array2);
                node<DataStructures::LectureInfo, int> ** p1 = array1;
                node<DataStructures::LectureInfo, int> ** p2 = array2;
            int x=0, y=0;
                while(x+y < m+n){
                    if(x < m && y < n){
                        if(p1[x]->getKey() < p2[y]->getKey()){
                        array3[x+y] = p1[x];
                        x++;
                        }else{
                            array3[x+y] = p2[y];
                            y++;
                        }
                    }else if(x ==m){
                        array3[x+y] = p2[y];
                        y++;
                    }else{
                        array3[x+y] = p1[x];
                        x++;
                    }
                }
            delete[] array1;
            delete[] array2;
            AVLTree<DataStructures::LectureInfo, int>* newTree = treeFill(array3, m+n);
            delete []array3;
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
        root->setLeft(nullptr);
        root->setRight(nullptr);
        int middle = start+(finish - start)/2;
        if(middle-start>1 || (start == 0 && middle-start == 1)){
            root->setLeft(array[start+(middle-start)/2]);
            treeFill_aux(root->getLeft(),array,start,middle);
        }
        if(finish-middle>1){
            root->setRight(array[middle+(finish-middle)/2]);
            treeFill_aux(root->getRight(),array,middle,finish);
        }
    }
    AVLTree<DataStructures::LectureInfo, int>* treeFill(node<DataStructures::LectureInfo, int> ** array, int m){
        node<DataStructures::LectureInfo, int> *root = array[m/2];
        treeFill_aux(root, array, 0, m);
        return new AVLTree<DataStructures::LectureInfo, int>(root,m);
    }
    ///////////////////////
    
	void CalculateScheduleEfficiency(float *efficiency){
        *efficiency = timeTable->getEfficiency();
        if(*efficiency == -1) throw Failure();
    }
    void GetAllFreeRoomsByHour(int hour, int **rooms, int* numOfRooms){
        //check for exceptions
        timeTable->getFreeRoomsAtHour(hour, rooms, numOfRooms);
    }
    void GetAllLecturesByCourse(int courseID, int **hours, int **rooms, int *numOfLectures){
        if(courseID <= 0 || !hours || !rooms || !numOfLectures) throw IllegalInitialization();
        
        course currCourse = courses->getData(courseID);
        int dataNum = currCourse.getLecNum();
        node<LectureInfo, int>** data = new node<LectureInfo, int>*[dataNum];
        currCourse.getScheduled()->fillAnArray(data);
        *hours = new int[dataNum];
        *rooms = new int[dataNum];
        for (int i = 0; i < dataNum; i++) {
            (*hours)[i] = (data[i]->getKey().getHour());
            (*rooms)[i] = (data[i]->getKey().getRoom());
        }
        *numOfLectures = dataNum;
        delete[] data;
    }
    ~CS_system(){
        delete timeTable;
        delete courses;
    }
};

#endif /* Schedule_hpp */
