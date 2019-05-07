//
//  AVL.cpp
//  Data Structures HW2
//
//  Created by Ezzat Qupty on 16/04/2019.
//  Copyright © 2019 Ezzat Qupty. All rights reserved.
//

#include "AVL.hpp"
#include "Course.hpp"
#include "Lecture_Info.hpp"
#include "Schedule.hpp"
int main(){
	using DataStructures::AVLTree;
	using DataStructures::printTree;
	AVLTree<int, int> a;
	a.insert(13,13);
	printTree(a.getRoot(), nullptr, false);
	a.insert(8,8);
	printTree(a.getRoot(), nullptr, false);
	a.insert(15,15);
	printTree(a.getRoot(), nullptr, false);
	a.insert(4,4);
	printTree(a.getRoot(), nullptr, false);
	a.insert(18,18);
	printTree(a.getRoot(), nullptr, false);
	a.remove(4);
	printTree(a.getRoot(), nullptr, false);
	a.remove(13);
	printTree(a.getRoot(), nullptr, false);
	a.remove(18);
	printTree(a.getRoot(), nullptr, false);
	a.remove(8);
	printTree(a.getRoot(), nullptr, false);
	a.remove(15);
	printTree(a.getRoot(), nullptr, false);
	return 0;
}
