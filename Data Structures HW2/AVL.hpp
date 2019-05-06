//
//  AVL.hpp
//  Data Structures HW2
//
//  Created by Ezzat Qupty on 16/04/2019.
//  Copyright © 2019 Ezzat Qupty. All rights reserved.
//

#ifndef AVL_hpp
#define AVL_hpp

#include <string>
#include <exception>
#include <iostream>
#include <stdbool.h>
#include "Exceptions.hpp"

namespace DataStructures{
	
	template < class K, class D>
	class node{
		K* key;
		D* data;
		node* parent;
		node* left;
		node* right;
		int kids;
		
	public:
		
		int BF;
		int height;
		
		node(const K& key, D& data): key(nullptr), data(nullptr), parent(nullptr), left(nullptr), right(nullptr), kids(0), BF(0), height(0){
			try{
				this->key = new (std::nothrow) K(key);
				this->data = new (std::nothrow) D(data);
			} catch (std::bad_alloc e){ throw OutOfMemory();}
		}
		
		node(node& n){
			try{
				this->key = new (std::nothrow) K(key);
				this->data = new (std::nothrow) D(data);
			} catch (std::bad_alloc e){ throw OutOfMemory();}
			this->parent = n->parent;
			this->left = n->left;
			this->right = n->right;
			this->kids = n->kids;
			this->BF = n->BF;
			this->height = n->heigh;
		}
		node& operator=(const node& n){
			if(*this == n) return &this;
			if(this->key) delete this->key;
			if(this->data) delete this->data;
			this(n);
			return &this;
		}

		~node(){
			delete key;
			delete data;
		}
		
		bool operator==(node* n){
			return n->key == key && n->data == data && n->left == left && n->right == right && n->parent == parent;
		}
		
		K& getKey() { return *key;}
		D& getData() { return *data;}
		D* getDataPtr(){return data;}
		K* getKeyPtr(){return key;}
		int getKids() { return kids;}
		int getBF() { update(); return BF;}
		int getHeight() { update(); return height;}
		
		node* getLeft(){ return left;}
		node* getRight(){ return right;}
		node* getParent(){ return parent;}
		
		void setDataPtr(D* data){this->data = data;}
		void setKeyPtr(K* key){this->key = key;}
		void setKey(K& key){
			if(this->key){
				delete this->key;
			}
			try{
				this->key = new (std::nothrow) K(key);
			} catch (std::bad_alloc e){ throw OutOfMemory();}
		}
		
		void setData(D& data){
			if(this->data){
				delete this->data;
			}
			try{
				this->data = new (std::nothrow) D(data);
			} catch (std::bad_alloc e){ throw OutOfMemory();}
		}
		
		void setLeft(node* n){
			if(!n && !left){
			}
			if(!n && left){
				left = nullptr;
				kids--;
			}
			if(n && !left){
				left = n;
				kids++;
			}
			if(n && left){
				left = n;
			}
			update();
		}
		
		void setRight(node* n){
			if(!n && !right){
			}
			else if(!n && right){
				right = nullptr;
				kids--;
			}
			else if(n && !right){
				right = n;
				kids++;
			}
			else {
				right = n;
			}
			update();
		}
		
		void setParent(node* n){ this->parent = n;}
		
		void removeLeft(){
			if(!left) return;
			left = nullptr;
			kids--;
			update();
		}
		
		void removeRight(){
			if(!right) return;
			right = nullptr;
			kids--;
			update();
		}
		
		void removeParent(node* n){
			if(!parent) return;
			this->parent = nullptr;
		}
		
		void update(){
			if(left) left->update();
			if(right) right->update();
			int lheight = left ? left->height : 0;
			int rheight = right ? right->height : 0;
			height = lheight > rheight ? lheight : rheight;
			height++;
			BF = lheight - rheight;
		}
		
	};
	
	//Assuming class K has comparing operators
	template< class K, class D>
	class AVLTree {
		node<K, D>* root;
		int nodeCount;
		
		void deleteSubTree(node<K,D>* root);
		void insert_aux(node<K, D>* n, node<K, D>* in);
		void remove_aux(const K& key, node<K,D>* n);
		void balance(node<K, D>* n);
		void balanceAll(node<K,D>* son);
		node<K,D>* copyNodes(node<K,D>* head, node<K,D>* parent);
		node<K,D>* getData_aux(const K& key, node<K,D>* node);
		void swapNodes(node<K, D>* a, node<K, D>* b);
		
	public:
		AVLTree(): root(nullptr), nodeCount(0){}
		~AVLTree();
		AVLTree(AVLTree& avl){
			this->head = copyNodes(avl->head, nullptr);
			nodeCount = avl->nodeCount;
		}
		
		AVLTree& operator=(const AVLTree& avl){
			if(*this == avl) return &this;
			this(avl);
			return &this;
		}
        
		node<K,D>* getRoot(){ return root;}
		
		D& getData(const K& key){
			node<K,D>* n = getData_aux(key, root);
            if(!n) throw DoesNotExist();
			return n->getData();
		}
		
		int getNodeCount(){ return nodeCount;}
		
		bool contains(const K& key);
		
		void insert(const K& key, D data);
		void remove(const K& key);
		
		void rotateLeft(node<K,D>* node);
		void rotateRight(node<K,D>* node);
		
		bool isBalanced(){return isBalanced_aux(root);}
		bool isBalanced_aux(node<K,D>* n){
			if(!n) return true;
			if(n->getBF() < -1 || n->getBF() > 1) return false;
			else return isBalanced_aux(n->getLeft()) && isBalanced_aux(n->getRight());
		}
	};
	
	template<class K, class D>
	AVLTree<K,D>::~AVLTree(){
		if(root) deleteSubTree(root);
	}
	
	//Copies all subtree of given head (parent pointer is for setting the heads parent node)
	template<class K, class D>
	node<K,D>* AVLTree<K,D>::copyNodes(node<K,D>* head, node<K,D>* parent){
		if(!head) return;
		node<K, D>* new_n = new (std::nothrow) node<K, D>(head);
		if(!new_n) throw OutOfMemory();
		new_n->setParent(parent);
		new_n->setLeft(AVLTree<K,D>::copyNodes(head->getLeft(), new_n));
		new_n->setRight(AVLTree<K,D>::copyNodes(head->getRight(), new_n));
		return new_n;
	}
	
	//Swaps location of two given nodes (this is used for a special case in the remove function)
	template<class K, class D>
	void AVLTree<K,D>::swapNodes(node<K,D>* a, node<K,D>* b){
		K* tempKey = a->getKeyPtr();
		D* tempData = a->getDataPtr();
		a->setKeyPtr(b->getKeyPtr());
		a->setDataPtr(b->getDataPtr());
		b->setKeyPtr(tempKey);
		b->setDataPtr(tempData);
	}

	//deletes passed noode and all its children.
	template<class K, class D>
	void AVLTree<K,D>::deleteSubTree(node<K, D>* root){
		if(root){
			deleteSubTree(root->getLeft());
			deleteSubTree(root->getRight());
			delete root;
		}
	}
	
	//Function looks if the key exists in the current tree.
	template<class K, class D>
	bool AVLTree<K,D>::contains(const K& key){ return AVLTree<K,D>::getData_aux(key, root);}
	
	template<class K, class D>
	node<K,D>* AVLTree<K,D>::getData_aux(const K& key, node<K,D>* node){
		if(!node) return nullptr;
		K node_key = node->getKey();
		if(key == node_key) return node;
		if(key < node_key) return getData_aux(key, node->getLeft());
		if(key > node_key) return getData_aux(key, node->getRight());
		return nullptr;
	}
	
	//inserts new node in its right place
	//throws OUtOfMemory if there is an allocatiion problem
	//throws Already Exists if Key exists.0
	template <class K, class D>
	void AVLTree<K, D>::insert(const K& key, D data){
		node<K, D>* new_n = new (std::nothrow) node<K, D>(key, data);
		if(!new_n) throw OutOfMemory();
		if(!this->root){
			root = new_n;
			nodeCount++;
		}
		else insert_aux(this->root, new_n);
	}
	
	//recursive algorithm to find and insert a key and data in the correct place
	template <class K, class D>
	void AVLTree<K, D>::insert_aux(node<K, D>* n, node<K, D>* in){
		if(n->getData() == in->getData()) throw AlreadyExists();
		if(n->getData() > in->getData()){
			if(n->getLeft()){
				AVLTree<K,D>::insert_aux(n->getLeft(),in);
				n->update();
			}
			else {
				n->setLeft(in);
				in->setParent(n);
				n->update();
				nodeCount++;
			}
		}
		else if(n->getRight()){
			AVLTree<K,D>::insert_aux(n->getRight(), in);
			n->update();
		}
		else {
			n->setRight(in);
			in->setParent(n);
			n->update();
			nodeCount++;
		}
		balance(n);
	}
	
	//Removes node  of given key while maintaining balance of the tree
	template<class K, class D>
	void AVLTree<K,D>::remove(const K& key){
		remove_aux(key, root);
	}
	
	template<class K, class D>
	void AVLTree<K,D>::remove_aux(const K& key, node<K,D>* n){
		if(!n) return;
		node<K,D>* parent = n->getParent();
		if(n->getKey() == key){
			if(n->getKids() == 0){
				if(n == root) root = nullptr;
				else if(parent->getLeft() == n) parent->setLeft(nullptr);
				else if(parent->getRight() == n) parent->setRight(nullptr);
				nodeCount--;
				delete n;
				balanceAll(parent);
				return;
			}
			else if(n->getKids() == 1){
				node<K,D>* son = nullptr;
				if(n->getLeft()) son = n->getLeft();
				else son = n->getRight();
				if(n == root) root = son;
				else if(parent->getLeft() == n) parent->setLeft(son);
				else if(parent->getRight() == n) parent->setRight(son);
				nodeCount--;
				delete n;
				balanceAll(parent);
				return;
			}
			else {
				node<K,D>* itr = n->getRight();
				while(itr && itr->getLeft()){
					itr = itr->getLeft();
				}
				swapNodes(n, itr);
				AVLTree<K,D>::remove_aux(key, itr);
			}
		}
		else if(n->getKey() > key) AVLTree<K,D>::remove_aux(key, n->getLeft());
		else AVLTree<K,D>::remove_aux(key, n->getRight());
	}
	
	//Depending on whoich situation the tree is in, performs needed rotations to
	// keep tree balanced
	template<class K, class D>
	void AVLTree<K, D>::balance(node<K, D>* n){
		if(!n) return;
		if(n->getLeft()){
			if(n->BF == 2 && n->getLeft()->BF == -1){    //LR
				rotateLeft(n->getLeft());
				rotateRight(n);
			}
			if(n->BF == 2 && n->getLeft()->BF >= 0){     //LL
				rotateRight(n);
			}
		}
		if(n->getRight()){
			if(n->BF == -2 && n->getRight()->BF <= 0){   //RR
				rotateLeft(n);
			}
			if(n->BF == -2 && n->getRight()->BF == 1){    //RL
				rotateRight(n->getRight());
				rotateLeft(n);
			}
		}
	}

	//Balances all nodes in path from son to root
	template<class K, class D>
	void AVLTree<K,D>::balanceAll(node<K,D>* son){
		if(!son) return;
		son->update();
		balance(son);
		balanceAll(son->getParent());
	}
	
	//Does a right rotation on the passed node
	template<class K, class D>
	void AVLTree<K, D>::rotateRight(node<K,D>* n){
		node<K, D>* pivot = n->getLeft();
		node<K, D>* pivRight = pivot ? pivot->getRight() : nullptr;
		node<K,D>* nParent = n->getParent();
		n->setLeft(pivRight);
		pivot->setRight(n);
		if(n == root) root = pivot;
		else if(nParent->getLeft() == n) nParent->setLeft(pivot);
		else if(nParent->getRight() == n) nParent->setRight(pivot);
		pivot->setParent(n->getParent());
		n->setParent(pivot);
		if(pivot->getLeft()) pivot->getLeft()->setParent(pivot);
		if(pivot->getRight()) pivot->getRight()->setParent(pivot);
		n->update();
		pivot->update();
	}
	
	//Does a left rotation on the passed node
	template<class K, class D>
	void AVLTree<K, D>::rotateLeft(node<K,D>* n){
		node<K,D>* pivot = n->getRight();
		node<K,D>* pivLeft = pivot ? pivot->getLeft() : nullptr;
		node<K,D>* nParent = n->getParent();
		n->setRight(pivLeft);
		pivot->setLeft(n);
		if(n == root) root = pivot;
		else if(nParent->getLeft() == n) nParent->setLeft(pivot);
		else if(nParent->getRight() == n) nParent->setRight(pivot);
		pivot->setParent(n->getParent());
		n->setParent(pivot);
		if(pivot->getLeft()) pivot->getLeft()->setParent(pivot);
		if(pivot->getRight()) pivot->getRight()->setParent(pivot);
		n->update();
		pivot->update();
	}
	
	
	/////////////////////////PRINTING FUNCTION AND AUX//////////////////////////////
	struct Trunk
	{
		Trunk *prev;
		std::string str;
		
		Trunk(Trunk *prev, std::string str)
		{
			this->prev = prev;
			this->str = str;
		}
	};
	
	void showTrunks(Trunk *p) {
		if (p == nullptr)
			return;
		
		showTrunks(p->prev);
		
		std::cout << p->str;
	}
	
	template<class K, class D>
	void printTree(node<K,D>* root, Trunk *prev, bool isLeft){
		if (root == nullptr)
			return;
		
		std::string prev_str = "	";
		Trunk *trunk = new Trunk(prev, prev_str);
		
		printTree(root->getLeft(), trunk, true);
		
		if (!prev)
			trunk->str = "---";
		else if (isLeft)
		{
			trunk->str = ".---";
			prev_str = "   |";
		}
		else
		{
			trunk->str = "`---";
			prev->str = prev_str;
		}
		
		showTrunks(trunk);
		std::cout << root->getData() << std::endl;
		
		if (prev)
			prev->str = prev_str;
		trunk->str = "   |";
		
		printTree(root->getRight(), trunk, false);
	}
	////////////////////////////////////////////////////////////////////////////////
	
}

#endif /* AVL_hpp */
