//
//  Exceptions.hpp
//  Data Structures HW2
//
//  Created by Ezzat Qupty on 05/05/2019.
//  Copyright © 2019 Ezzat Qupty. All rights reserved.
//

#ifndef Exceptions_hpp
#define Exceptions_hpp

#include <exception>
#include <string>

namespace DataStructures{
	
	class DSException : public std::exception{
	public:
		virtual ~DSException() throw() {}
	};
	class NullArg: public DSException{
		
	};
	
	class IllegalInitialization : public DSException {
	public:
		std::string what(){
			return "DSError: Illegal initialization values";
		}
	};
	
	class OutOfMemory : public DSException {
	public:
		std::string what(){
			return "DSError: Out of memory";
		}
	};
	
	class AlreadyExists : public DSException {
	public:
		std::string what(){
			return "DSError: Element exists";
		}
	};
	
	class DoesNotExist : public DSException {
	public:
		std::string what(){
			return "DSError: Element does not exist";
		}
	};
	
	class Failure : public DSException {
	public:
		std::string what(){
			return "DSError: Action failed";
		}
	};
	
}

#endif /* Exceptions_hpp */
