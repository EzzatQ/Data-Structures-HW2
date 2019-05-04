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
#include <stdio.h>
#include <stdbool.h>

namespace DataStructures{
	
	class DSException : public std::exception{
	public:
		virtual ~DSException() throw() {}
	};
	class Null_Arg: public DSException{
		
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
			return "DSError: Key already exists";
		}
	};
	
	template < class K, class D>
	class node{
		K key;
		D data;
		node* parent;
		node* left;
		node* right;
		int kids;
		
	public:
		
		int BF;
		int height;
		
		node(const K& key, D& data): key(key), data(data), parent(nullptr), left(nullptr), right(nullptr), kids(0), BF(0), height(0){}
		
		node(node& n){
			this->key = n->key;
			this->data = n->data;
			this->parent = n->parent;
			this->left = n->left;
			this->right = n->right;
			this->kids = n->kids;
			this->BF = n->BF;
			this->height = n->heigh;
		}
		node& operator=(const node& n){
			this(n);
			return &this;
		}
		
		~node(){}
		const K& getKey() const { return key;}
		const D& getData() const { return data;}
		const int getKids() const {return kids;}
		const int getBF() const { update(); return BF;}
		const int getHeight() const { update(); return height;}
		
		node* getLeft(){ return left;}
		node* getRight(){ return right;}
		node* getParent(){ return parent;}
		
		void setLeft(node* n){
			if(!n && !left){
				return;
			}
			if(!n && left){
				left = nullptr;
				kids--;
				return;
			}
			if(n && !left){
				left = n;
				kids++;
			}
			if(n && left){
				left = n;
				return;
			}
			update();
		}
		
		void setRight(node* n){
			if(!n && !right){
				return;
			}
			if(!n && right){
				right = nullptr;
				kids--;
				return;
			}
			if(n && !right){
				right = n;
				kids++;
			}
			if(n && right){
				right = n;
				return;
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
			height++; ///???
			BF = lheight - rheight;
		}
		
	};
	
	//Assuming class K has comparing operators
	template< class K, class D>
	class AVLTree {
		node<K, D>* root;
		int nodeCount;
		
		void deleteSubTree(node<K,D>* root);
		bool contains(const K& key);
		bool contains_aux(K& key, node<K,D>* node);
		void insert_aux(node<K, D>* n, node<K, D>* in);
		void remove_aux(const K& key, node<K,D>* n);
		void balance(node<K, D>* n);
		void balanceAll(node<K,D>* son);
		node<K,D>* copyNodes(node<K,D>* head, node<K,D>* parent);
	public: void swapNodes(node<K, D>* a, node<K, D>* b);
		
	public:
		AVLTree(): root(nullptr), nodeCount(0){}
		~AVLTree();
		AVLTree(AVLTree& avl){
			this->head = copyNodes(avl->head, nullptr);
			nodeCount = avl->nodeCount;
		}
		
		AVLTree& operator=(const AVLTree& avl){
			this(avl);
			return &this;
		}
        
		node<K,D>* getRoot(){ return root;}
		
		void insert(const K& key, D data);
		void remove(const K& key);
		
		//		void preOrder(node<K,D>* node) const;
		//		void inOrder(node<K,D>* node) const;
		//		void postOrder(node<K,D>* node) const;
		
		void rotateLeft(node<K,D>* node);
		void rotateRight(node<K,D>* node);
	};
	
	template<class K, class D>
	AVLTree<K,D>::~AVLTree(){
		if(root) deleteSubTree(root);
	}
	
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
	
	template<class K, class D>
	void AVLTree<K,D>::swapNodes(node<K,D>* a, node<K,D>* b){
		node<K,D>* aParent = a->getParent();
		node<K,D>* bParent = b->getParent();
		if(aParent == bParent){
			if(a == root && b != root) root = b;
			if(b == root && a != root) root = a;
			if(aParent->getLeft() == a){
				aParent->setLeft(b);
				aParent->setRight(a);
			}
			else{
				aParent->setLeft(a);
				aParent->setRight(b);
			}
		} else {
		if(a == root && b != root) root = b;
		else if(aParent->getLeft() == a) aParent->setLeft(b);
		else if(aParent->getRight() == a) aParent->setRight(b);
		if(b == root && a != root) root = a;
		else if(bParent->getLeft() == b) bParent->setLeft(a);
		else if(bParent->getRight() == b) bParent->setRight(a);
		}
		node<K,D>* tempR = a->getRight();
		node<K,D>* tempL = a->getLeft();
		a->setRight(b->getRight());
		a->setLeft(b->getLeft());
		b->setRight(tempR);
		b->setLeft(tempL);
		if(a->getLeft()) a->getLeft()->setParent(b);
		if(a->getRight()) a->getRight()->setParent(b);
		if(b->getLeft()) b->getLeft()->setParent(a);
		if(b->getRight()) b->getRight()->setParent(a);

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
	
	//Function looks ifthe key exists in the current tree.
	template<class K, class D>
	bool AVLTree<K,D>::contains(const K& key){ AVLTree<K,D>::contains_aux(key, root);}
	
	template<class K, class D>
	bool AVLTree<K,D>::contains_aux(K& key, node<K,D>* node){
		K node_key = node->getKey();
		if(key == node_key) return true;
		if(key < node_key) return contains_aux(key, node->getLeft());
		if(key > node_key) return contains_aux(key, node->getRight());
		return false;
	}
	
	
	
	//inserts new node in its right place
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
		if(n->getData() >= in->getData()){
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
				else if(n->getParent()->getLeft() == n) n->getParent()->setLeft(nullptr);
				else if(n->getParent()->getRight() == n) n->getParent()->setRight(nullptr);
				delete n;
			}
			else if(n->getKids() == 1){
				node<K,D>* son = nullptr;
				if(n->getLeft()) son = n->getLeft();
				else son = n->getRight();
				if(n == root) root = son;
				else if(n->getParent()->getLeft() == n) n->getParent()->setLeft(son);
				else if(n->getParent()->getRight() == n) n->getParent()->setRight(son);
				delete n;
			}
			else {
				node<K,D>* itr = n->getRight();
				while(itr && itr->getLeft()){
					itr = itr->getLeft();
				}
				swapNodes(n, itr);
				AVLTree<K,D>::remove_aux(key, n);
			}
		}
		else if(n->getKey() > key) AVLTree<K,D>::remove_aux(key, n->getLeft());
		AVLTree<K,D>::remove_aux(key, n->getRight());
		balanceAll(parent);
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

	template<class K, class D>
	void AVLTree<K,D>::balanceAll(node<K,D>* son){
		if(!son) return;
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
