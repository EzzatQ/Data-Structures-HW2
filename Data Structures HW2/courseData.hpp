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
using namespace DataStructures;
class course{
    int courseNum;
    AVLTree<int, int> reserved;
public:
    course(int number): courseNum(number){
        //initializing the tree
    };
};
#endif /* courseData_hpp */

