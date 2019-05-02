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
		
		int BL;
		
		node(const K& key, D& data): key(key), data(data), parent(nullptr), left(nullptr), right(nullptr), kids(0), BL(0){}
		
		node(node& n){
			this->key = n->key;
			this->data = n->data;
			this->parent = n->parent;
			this->left = n->left;
			this->right = n->right;
			this->kids = n->kids;
			this->BL = n->BL;
		}
		node& operator=(const node& n){
			this(n);
			return &this;
		}
		
		~node(){}
		const K& getKey() const { return key;}
		const D& getData() const { return data;}
		const int getKids() const {return kids;}
		const int getBL() const {return BL;}
		node* getLeft(){ return left;}
		node* getRight(){ return right;}
		node* getParent(){ return parent;}
		
		void setLeft(node* n){
			if(!n && !this->left){
				return;
			}
			if(!n && this->left){
				this->left = nullptr;
				kids--;
				return;
			}
			if(n && !this->left){
				this->left = n;
				kids++;
			}
			if(n && this->left){
				this->left = n;
				return;
			}
		}
		
		void setRight(node* n){
			if(!n && !this->right){
				return;
			}
			if(!n && this->right){
				this->right = nullptr;
				kids--;
				return;
			}
			if(n && !this->right){
				this->right = n;
				kids++;
			}
			if(n && this->right){
				this->right = n;
				return;
			}
		}
		
		void setParent(node* n){ this->parent = n;}
		
		void removeLeft(){
			this->left = nullptr;
			kids--;
		}
		
		void removeRight(){
			this->right = nullptr;
			kids--;
		}
		
		void removeParent(node* n){ this->parent = nullptr;}
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
		void balance(node<K, D>* n);
		node<K,D>* copyNodes(node<K,D>* head, node<K,D>* parent);
		
	public:
		AVLTree(): root(nullptr), nodeCount(0){}
		~AVLTree();
		AVLTree(AVLTree& avl){
			this->head = copyNodes(avl->head, nullptr);
			this->treeHight = avl->treeHight;
			this->nodeCount = avl->nodeCount;
		}
		AVLTree& operator=(const AVLTree& avl){
			this(avl);
			return &this;
		}
		node<K,D>* getRoot(){ return root;}
		int getNodeCount(){ return nodeCount;}
		
		void insert(const K& key, D data);

//		STILL GOTTA DO THESE FUNCTIONS
//		int getHight(const node<K,D>* node) const;
//		int getBF(const node<K,D>* node) const;
//
//		void preOrder(node<K,D>* node) const;
//		void inOrder(node<K,D>* node) const;
//		void postOrder(node<K,D>* node) const;
		
		static void rotateLeft(node<K,D>* node);
		static void rotateRight(node<K,D>* node);
		
	};
	
	template<class K, class D>
	AVLTree<K,D>::~AVLTree(){
		if(root) deleteSubTree(root);
	}
	
	//deletes passed noode and all its children.0
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
	
	//inserts new node
	template <class K, class D>
	void AVLTree<K, D>::insert(const K& key, D data){
		node<K, D>* new_n = new (std::nothrow) node<K, D>(key, data);
		if(!new_n) throw OutOfMemory();
		if(!this->root){
			root = new_n;
			
		}
		else insert_aux(this->root, new_n);
	}
	
	
	//recursive algorithm to find and insert a key and data in the correct place
	template <class K, class D>
	void AVLTree<K, D>::insert_aux(node<K, D>* n, node<K, D>* in){
		if(n->getData() <= in->getData()){
			if(n->getLeft()){
				AVLTree<K,D>::insert_aux(n->getLeft(),in);
				n->BL++;
			}
			else {
				n->setLeft(in);
				in->setParent(n);
				n->BL++;
			}
		}
		else if(n->getRight()){
			AVLTree<K,D>::insert_aux(n->getRight(), in);
			n->BL--;
		}
		else {
			n->setRight(in);
			in->setParent(n);
			n->BL--;
		}
		balance(n);
	}

	//Depending on whoich situation the tree is in, performs needed rotations to
	// keep tree balanced
	template<class K, class D>
	void AVLTree<K, D>::balance(node<K, D>* n){
		if(!n) return;
		if(n->BL == 2 && n->getLeft()->BL == -1){    //LR
			rotateRight(n->getLeft());
			rotateLeft(n);
		}
		if(n->BL == 2 && n->getLeft()->BL >= 0){     //LL
			rotateLeft(n);
		}
		if(n->BL == -2 && n->getRight()->BL <= 0){   //RR
			rotateRight(n);
		}
		if(n->BL == -2 && n->getRight()->BL == 1){    //RL
			rotateLeft(n->getRight());
			rotateLeft(n);
		}
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
	
	//i think theres a bug here: we need to think oh how to do this when r and l
	//can also be nullptr. and theres a  mikre katseh. when n = head, we need to
	//change the head of the tree itself and update the parrent of the node!
	template<class K, class D>
	void AVLTree<K, D>::rotateRight(node<K,D>* n){
		if(!n) return;
		node<K, D>* r = n;
		node<K, D>* l = n->getLeft();
		node<K, D>* rParent = !r ? nullptr : r->getParent();
		node<K, D>* lParent = !l ? nullptr : l->getParent();
		node<K, D>* lRight = !l ? nullptr : l->getRight();
		r->setParent(lParent);
		lRight->setParent(r);
		l->setParent(rParent);
		r->setLeft(lRight);
		l->setRight(r);
		n = l;
		r->BL += 1;					//////////////
		if (l->BL < 0) r->BL += -l->BL;
		l->BL += 1;
		if (r->BL > 0) l->BL += r->BL;
	}
	
	//SAME EXACT THING HERE
	template<class K, class D>
	void AVLTree<K, D>::rotateLeft(node<K,D>* n){
		if(!n) return;
		node<K, D>* l = n;
		node<K, D>* r = n->getRight();
		node<K, D>* lParent = !l ? nullptr : l->getParent();
		node<K, D>* rLeft = !r ? nullptr : r->getLeft();
		l->setParent(r);
		rLeft->setParent(l);
		r->setParent(lParent);
		l->setRight(rLeft);
		r->setLeft(l);
		n = r;
		l->BL -= 1;
		if (r->BL > 0) l->BL -= r->BL;
		r->BL -= 1;
		if (l->BL < 0) r->BL -= -l->BL;
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
