//
//  courseData.hpp
//  Data Structures HW2
//
//  Created by Hasan Egbarie on 04/05/2019.
//  Copyright © 2019 Ezzat Qupty. All rights reserved.
//

#ifndef courseData_hpp
#define courseData_hpp

#include <stdio.h>
#include "AVL.hpp"
namespace DataStructures{
    class course{
        int courseNum;
        AVLTree<int, int>* reserved;
    public:
        course(int number): courseNum(number){
            
        }
        int getCourseID()const{ return courseNum; };
    };
    bool operator>(const course& a,const course& b){
        return (a.getCourseID() > b.getCourseID());
    }
    bool operator<(const course& a,const course& b){
        return (a.getCourseID() < b.getCourseID());
    }
    bool operator==(const course& a,const course& b){
        return (a.getCourseID() == b.getCourseID());
    }
}
#endif /* courseData_hpp */

