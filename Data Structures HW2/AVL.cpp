//
//  AVL.cpp
//  Data Structures HW2
//
//  Created by Ezzat Qupty on 16/04/2019.
//  Copyright © 2019 Ezzat Qupty. All rights reserved.
//

#include "AVL.hpp"
int main(){
	using DataStructures::AVLTree;
	using DataStructures::printTree;
	AVLTree<int, int> a;
	a.insert(1,1);
	printTree(a.getRoot(), nullptr, false);
	a.insert(0,0);
	printTree(a.getRoot(), nullptr, false);
	a.insert(2,2);
	printTree(a.getRoot(), nullptr, false);
	
}
