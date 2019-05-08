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
#include "Course.hpp"
int main(){
	using DataStructures::AVLTree;
	using DataStructures::printTree;
	AVLTree<int, int> a;
	a.insert(8,8);
	printTree(a.getRoot(), nullptr, false);
	a.insert(3,3);
	printTree(a.getRoot(), nullptr, false);
	a.insert(5,5);
	printTree(a.getRoot(), nullptr, false);
	a.insert(2,2);
    a.insert(13,13);
	printTree(a.getRoot(), nullptr, false);
    std::cout << "------------------------------------------------------\n";
	a.insert(11,11);
    printTree(a.getRoot(), nullptr, false);
    a.insert(20,20);
	printTree(a.getRoot(), nullptr, false);
    std::cout << "------------------------------------------------------\n";
    ////
	a.remove(3);
	printTree(a.getRoot(), nullptr, false);

	return 0;
}
