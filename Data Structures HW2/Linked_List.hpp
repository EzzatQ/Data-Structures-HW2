//
//  Linked List.hpp
//  Data Structures HW2
//
//  Created by Ezzat Qupty on 05/05/2019.
//  Copyright © 2019 Ezzat Qupty. All rights reserved.
//

#ifndef Linked_List_hpp
#define Linked_List_hpp

#include "Exceptions.hpp"

namespace DataStructures{
	
	template<class D>
	class LLnode{
		D& data;
		LLnode* prev;
		LLnode* next;
	public:
		LLnode(D& d): data(d), prev(nullptr), next(nullptr){}
		~LLnode();
		LLnode(LLnode& n);
		LLnode& operator=(LLnode& n);
		void setPrev(LLnode* p){ prev = p; }
		void setNext(LLnode* n){ next = n; }
		LLnode* getPrev(){ return prev;  }
		LLnode* getNext(){ return next; }
	};
	
	template<class D>
	class LinkedList{
		LLnode<D>* head;
		int nodeCount;
	public:
		LinkedList(): nodeCount(0) {
			head = new (std::nothrow) LLnode<D>(nullptr);
			if(!head) throw OutOfMemory();
		}
		~LinkedList();
		LinkedList(LinkedList& ll);
		LinkedList& operator=(LinkedList& ll);
		LLnode<D>* getHead();
		int getNodeCount();
		void insert(D& data);
		void contains(D& data);
		D& getData(D& data);
		void remove(D& data);
		template<class Func>
		void applyToAll(Func& f);
	};
}


#endif /* Linked_List_hpp */
