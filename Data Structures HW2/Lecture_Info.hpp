//
//  Lecture_Info.hpp
//  Data Structures HW2
//
//  Created by Ezzat Qupty on 05/05/2019.
//  Copyright © 2019 Ezzat Qupty. All rights reserved.
//

#ifndef Lecture_Info_hpp
#define Lecture_Info_hpp


namespace DataStructures{
	class LectureInfo{
	public:
		int room;
		int hour;
		LectureInfo(int room, int hour): room(room), hour(hour){}
		~LectureInfo(){}
		LectureInfo(LectureInfo& lf);
		//operator =
		//operator ==
		//operator >
		//operator <
		//operator >=
		//operator <=
	};
}

#endif /* Lecture_Info_hpp */
