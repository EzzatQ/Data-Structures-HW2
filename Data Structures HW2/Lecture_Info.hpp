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
		int hour;
		int room;
		LectureInfo(int hour, int room): hour(hour), room(room){}
		~LectureInfo(){}
		LectureInfo(LectureInfo& li){
			hour = li.hour;
			room = li.room;
		}
		LectureInfo& operator=(LectureInfo& li){
			hour = li.hour;
			room = li.room;
			return *this;
		}
		bool operator==(const LectureInfo& li) const {
			return hour == li.hour && room == li.room;
		}
		bool operator>(const LectureInfo& li) const {
			if(hour > li.hour) return true;
			else if(hour < li.hour) return false;
			else return room > li.room;
		}
		bool operator<(const LectureInfo& li) const {
			if(hour < li.hour) return true;
			else if(hour > li.hour) return false;
			else return room < li.room;
		}
		bool operator>=(const LectureInfo& li) const {
			return operator>(li) || operator==(li);
		}
		bool operator<=(const LectureInfo& li) const {
			return operator<(li) || operator==(li);
		}
	};
}

#endif /* Lecture_Info_hpp */
