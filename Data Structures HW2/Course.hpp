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
#include "Lecture_Info.hpp"

namespace DataStructures{
	
	class course{
		int courseID;
		AVLTree<LectureInfo, int>* scheduled;
	public:
		course(int number): courseID(number), scheduled(nullptr){
			scheduled = new (std::nothrow) AVLTree<LectureInfo, int>();
			if(!scheduled) throw OutOfMemory();
		}
        course(course& newCourse){
            courseID = newCourse.getCourseID();
            scheduled = new AVLTree<LectureInfo, int>(*newCourse.getScheduled());
        }
		int getCourseID()const{ return courseID; }
        void setCourseID(int newID){courseID = newID; }
        AVLTree<LectureInfo, int>* getScheduled()const{ return scheduled; }
        void setScheduled(AVLTree<LectureInfo, int>* newSchedule){
            delete scheduled;
            //scheduled = new  AVLTree<LectureInfo, int>(*newSchedule);
            scheduled = newSchedule;
        }
		bool operator==(const course& c){
			return (courseID == c.courseID);
		}
		bool operator>(const course& c){
			return (courseID > c.courseID);
		}
		bool operator<(const course& c){
			return (courseID < c.courseID);
		}
		bool operator>=(const course& c){
			return (courseID >= c.courseID);
		}
		bool operator<=(const course& c){
			return (courseID <= c.courseID);
		}
        ~course(){delete scheduled;}
	};
	
}


#endif /* Course_hpp */
