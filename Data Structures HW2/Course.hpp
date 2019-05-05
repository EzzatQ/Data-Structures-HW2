//
//  Course.hpp
//  Data Structures HW2
//
//  Created by Ezzat Qupty on 05/05/2019.
//  Copyright © 2019 Ezzat Qupty. All rights reserved.
//

#ifndef Course_hpp
#define Course_hpp

#include "AVL.hpp"

namespace DataStructures{
	class course{
		int courseNum;
		AVLTree<int, int>* reserved;
	public:
		course(int number): courseNum(number), reserved(nullptr){
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


#endif /* Course_hpp */
