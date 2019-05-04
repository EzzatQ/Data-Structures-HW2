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
	a.insert(10,10);
	printTree(a.getRoot(), nullptr, false);
	a.insert(9,9);
	printTree(a.getRoot(), nullptr, false);
	a.insert(0,0);
	printTree(a.getRoot(), nullptr, false);
	a.insert(2,2);
	printTree(a.getRoot(), nullptr, false);
	a.insert(37, 37);
	printTree(a.getRoot(), nullptr, false);
	a.insert(18,18);
	printTree(a.getRoot(), nullptr, false);
	a.insert(1,1);
	printTree(a.getRoot(), nullptr, false);
	a.insert(39,39);
	printTree(a.getRoot(), nullptr, false);
	a.insert(4,4);
	printTree(a.getRoot(), nullptr, false);
	a.insert(4,4);
	printTree(a.getRoot(), nullptr, false);
//	a.swapNodes(a.getRoot(), a.getRoot()->getRight()->getLeft());
//	printTree(a.getRoot(), nullptr, false);
	a.remove(10);
	printTree(a.getRoot(), nullptr, false);
	a.remove(0);
	printTree(a.getRoot(), nullptr, false);
	a.remove(37);
	printTree(a.getRoot(), nullptr, false);
	a.remove(1);
	printTree(a.getRoot(), nullptr, false);
	a.remove(9);
	printTree(a.getRoot(), nullptr, false);
}
