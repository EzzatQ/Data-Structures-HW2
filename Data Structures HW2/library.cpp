//
//  library.cpp
//  Data Structures HW2
//
//  Created by Ezzat Qupty on 05/05/2019.
//  Copyright © 2019 Ezzat Qupty. All rights reserved.
//

#include "library.h"
#include "Schedule.hpp"

void *Init(int hours, int rooms){
    try{
        CS_system * DS = new CS_system(hours, rooms);
        return (void*)DS;
    }catch(IllegalInitialization a){
        return nullptr;
    }
}
StatusType AddLecture(void *DS, int hour, int roomID, int courseID) {
    if(!DS) return INVALID_INPUT;
    try{
        ((CS_system *)DS)->AddLecture(hour, roomID, courseID);
    }catch(IllegalInitialization a){
        return INVALID_INPUT;
    }catch(AlreadyExists a){
        return FAILURE;
    }
    return SUCCESS;
}
StatusType GetCourseID(void *DS, int hour, int roomID, int *courseID){
    if(!DS || !courseID) return INVALID_INPUT;
    int tmp = *courseID;
    try{
        ((CS_system *)DS)->GetCourseID(hour, roomID, courseID);
    }catch(IllegalInitialization a){
        return INVALID_INPUT;
    }
    if(*courseID==-1){
        *courseID = tmp;
        return FAILURE;
    }
    return SUCCESS;
}

StatusType DeleteLecture(void *DS, int hour, int roomID){
    if(!DS) return INVALID_INPUT;
    try{
       ((CS_system *)DS)->DeleteLecture(hour, roomID);
    }catch(IllegalInitialization a){
        return INVALID_INPUT;
    }catch(DoesNotExist a){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType ChangeCourseID(void *DS, int oldCourseID, int newCourseID){
    if(!DS) return INVALID_INPUT;
    try{
        ((CS_system *)DS)->ChangeCourseID(oldCourseID, newCourseID);
    }catch(IllegalInitialization a){
        return INVALID_INPUT;
    }catch(DoesNotExist a){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType CalculateScheduleEfficiency(void *DS, float *efficiency){
    if(!DS) return INVALID_INPUT;
    try{
        ((CS_system *)DS)->CalculateScheduleEfficiency(efficiency);
    }catch(Failure a){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetAllFreeRoomsByHour(void *DS, int hour, int **rooms, int* numOfRooms){
    if(!DS) return INVALID_INPUT;
    try{
        ((CS_system *)DS)->GetAllFreeRoomsByHour(hour, rooms, numOfRooms);
    }catch(IllegalInitialization a){
        return INVALID_INPUT;
    }catch(DoesNotExist a){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetAllLecturesByCourse(void *DS, int courseID, int **hours, int **rooms, int *numOfLectures){
    if(!DS) return INVALID_INPUT;
    try{
        ((CS_system *)DS)->GetAllLecturesByCourse(courseID, hours, rooms, numOfLectures);
    }catch(DoesNotExist a){
        return FAILURE;
    }catch(IllegalInitialization a){
        return INVALID_INPUT;
    }
    return SUCCESS;
}

void Quit(void** DS){
    if(*DS){
        delete (CS_system *)(*DS);
        *DS = nullptr;
    }
}
