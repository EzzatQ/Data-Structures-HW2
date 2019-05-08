#include <iostream>
#include <assert.h>
#include <ctime> // temporary for random tests
#include "AVL.hpp"

#define magicNumber 10

using namespace DataStructures;

void testAVLTree();
void testTreeBalance(AVLTree<int, int>& tree);

/*
 * Tree class should have:
 *      searchKey(int key) - return true/false, if [key] is already in tree
 *      insertElement(int key)
 *      deleteElement(int key)
 *      countNodesInTree - returns int; #nodes in tree
 *      checkIfBalance() - returns true/false, if tree is balance
 *      printTree(int *arr, (enum)InOrder) - scan the tree inorder and put the results inside arr.
 *          if the tree is valid binary search tree then arr should return sorted.
 */

int main() {
	srand(time(NULL)); //for random numbers in tests
	for(int i=1;i<3000;i++)
		testAVLTree();
}

void testAVLTree(){
	
	AVLTree<int, int> tree;
	int amountToInsert=rand()%magicNumber+1; //generate random number in range [1,magicNumber]
	int range=2*magicNumber;    //keys inserted into the tree are in range [1,2*magicNumber]
	
	for(int i=1;i<amountToInsert;i++){
		int keyToInsert=rand()%range + 1; // random number in range [1,magicNumber*2]
		if(!tree.contains(keyToInsert))
			tree.insert(keyToInsert, keyToInsert);
		
		testTreeBalance(tree); //Extra: check if tree is correct after every insert
	}
	std::cout << "-------------------------------------------\n";
	printTree(tree.getRoot(), nullptr, false);
	
	testTreeBalance(tree);
	
	int afterInsert = tree.getNodeCount();
	
	int elementsToRemove=rand()%(afterInsert+1); // choose randomly how many nodes to remove from tree
	
	int removalCounter=elementsToRemove;
	while(removalCounter!=0){
		int keyToRemove=rand()%range + 1; // random number in range [1,magicNumber*2]
		if(tree.contains(keyToRemove)){
			std::cout << keyToRemove << std::endl;
			tree.remove(keyToRemove);
			removalCounter--;
			printTree(tree.getRoot(), nullptr, false);
			testTreeBalance(tree); //Extra: check if tree is correct after every removal
		}
	}
	int afterRemoval=tree.getNodeCount();
	assert(afterRemoval+elementsToRemove==afterInsert); //make sure no branches in tree are lost during removal
	
	testTreeBalance(tree);
}

void testTreeBalance(AVLTree<int, int> &tree){
	
	assert(tree.isBalanced());
	
	//check if tree's inorder is sorted correctly
//	int nodesInTree=tree.getNodeCount();
//	int *arr=(int*)malloc((sizeof(*arr))*nodesInTree);
//	tree.printTree(arr,InOrder); //fill arr with the tree, by inorder. (InOrder is enum from AVLTree.h)
//	bool isSorted=true;
//	for(int i=1;i<nodesInTree;i++)
//		if(arr[i]<=arr[i-1])
//			isSorted = false;
//	free(arr);
//	assert(isSorted);
}
