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
		int BL;
		
	public:
		node(const K& key, const D& data): key(key), data(data), parent(parent), left(nullptr), right(nullptr), kids(0), BL(0){}
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
		node* getLeft(){ return left;}
		node* getRight(){ return right;}
		node* getParent(){ return parent;}
		
		void addLeft(node* n){
			this->left = n;
			kids++;
		}
		void addRight(node* n){
			this->right = n;
			kids++;
		}
		void addParent(node* n){ this->parent = n;}
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
		bool contains(K& key);
		bool contains_aux(K& key, node<K,D>* node);
		void insert_aux(node<K, D>* n, node<K, D>* in);
		void balance(node<K, D>* n);
		
	public:
		AVLTree(): root(nullptr), nodeCount(0){}
		~AVLTree();
		AVLTree(AVLTree& avl){ //need to copy all the nodes
			this->head = avl->head;
			this->treeHight = avl->treeHight;
			this->nodeCount = avl->nodeCount;
		}
		AVLTree& operator=(const AVLTree& avl){
			this(avl);
			return &this;
		}
		node<K,D>* getRoot(){ return root;}
		int getNodeCount(){ return nodeCount;}
		
		void insert(K& key, D& data);
		void deleteNode(node<K,D>* node);
		
		int getHight(node<K,D>* node) const;
		int getBF(node<K,D>* node) const;
		
		void preOrder(node<K,D>* node) const;
		void inOrder(node<K,D>* node) const;
		void postOrder(node<K,D>* node) const;
		
		static void rotateLeft(node<K,D>* node);
		static void rotateRight(node<K,D>* node);
		
	};
	
	template<class K, class D>
	AVLTree<K,D>::~AVLTree(){
		if(root) deleteSubTree(root);
	}
	
	template<class K, class D>
	void AVLTree<K,D>::deleteSubTree(node<K, D> *root){
		if(root){
			deleteSubTree(root->getLeft());
			deleteSubTree(root->getRight());
			delete root;
		}
		
	}
	
	template<class K, class D>
	bool AVLTree<K,D>::contains(K& key){ AVLTree<K,D>::contains_aux(key, root);}
	
	template<class K, class D>
	bool AVLTree<K,D>::contains_aux(K& key, node<K,D>* node){
		K node_key = node->getKey();
		if(key == node_key) return true;
		if(key < node_key) return contains_aux(key, node->getLeft());
		if(key > node_key) return contains_aux(key, node->getRight());
		return false;
	}
	
	template <class K, class D>
	void AVLTree<K, D>::insert(K& key, D& data){
		node<K, D>* new_n = new (std::nothrow) node<K, D>(key, data);
		if(!new_n) throw OutOfMemory();
		if(!this->root) root = new_n;
		else insert_aux(this->root, new_n);
	}
	
	template <class K, class D>
	void AVLTree<K, D>::insert_aux(node<K, D>* n, node<K, D>* in){
		if(n->getData() <= in->getData()){
			if(n->getLeft()){
				AVLTree<K,D>::insert_aux(n->getLeft(),in);
				n->BL++;
			}
			else {
				n->addLeft(in);
				in->SetParent(n);
				n->BL++;
			}
		}
		else if(n->getRight()) {
			AVLTree<K,D>::insert_aux(n->getRight(), in);
			n->BL--;
		}
		else {
			n->addRight(in);
			in->addParent(n);
			n->BL--;
		}
		balance(n);
	}
	
	template<class K, class D>
	void AVLTree<K, D>::balance(node<K, D>* n){
		if(n->Bb == 2 && n->getLeft() == -1);
		if(n->Bb == 2 && n->getLeft() >= 0);
		if(n->Bb == -2 && n->getRight() <= 0);
		if(n->Bb == -2 && n->getRight()() == 1);
		if(n->BF > 1){
			if(n->GetLeft()->BF < 0 ){
				rotateLeft( n->GetLeft() );
				rotateRight(n);
			}
		}
		else {
			if(n->GetRight()->BF > 0 ){
				rotateRight(n->GetRight());
				rotateLeft(n);
			}
		}
	}
	
	template<class K, class D>
	void AVLTree<K, D>::rotateLeft(node<K,D>* node){
		node<K, D>* B = n;
		node<K,D>* A = n->
	}
	
	template<class K, class D>
	void AVLTree<K, D>::rotateRight(node<K,D>* node){
		
	}
	
		
		
		//	void RotateRight(node* n){
		//		node* r = n;
		//		node* l = n->left;
		//		r->left = l->right;
		//		l->right = r;
		//		n = l;
		//		r->BL += 1;
		//		if (l->BL < 0) r->BL += -l->BL;
		//		l->BL += 1;
		//		if (r->BL > 0) l->BL += r->BL;
		//	}
		//
		//	void RotateLeft(node* n){
		//		node* r = n;
		//		node* l = n->right;
		//		r->right = l->left;
		//		l->left  = r;
		//		n = l;
		//		r->BL -= 1;
		//		if (l->BL > 0) r->BL -= l->BL;
		//		l->BL -= 1;
		//		if (r->BL < 0) l->BL -= -r->BL;
	
}
		
#endif /* AVL_hpp */
