/**
 *Author: Mingxuan Wang
 *PID: A53077257
 */
#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;

public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(0), isize(0) {  }


  /** Default destructor.
      Delete every node in this BST.
   */ // TODO
  virtual ~BST() {
    deleteHelper(root);              //call deleteHelper to delete all nodes in BST
    root = NULL;
    return;
  }

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return  true if the item was added to this BST
   *  as a result of this call to insert,
   *  false if an item equal to this one was already in this BST.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use >, <=, >=)
   */ // TODO
  virtual bool insert(const Data& item) {
    BSTNode<Data>** current = &root;             //The pointer to the current node,use this to keep track of the position where to insert, and assign the new node to it
    BSTNode<Data>* prev = NULL;                  //The cuurent node's previous node, a.k.a the parent node

    /*Find the place to insert the new node, return false when the node was already in the BST*/
    while ((*current) != NULL){
      prev = *current;
      if ((*current)->data == item){
        return false;
      }else if (item < (*current)->data ){
        current = &(*current)->left;
      }else{
        current = &(*current)->right;
      }
    }
    
    (*current) = new BSTNode<Data>(item);        //Create a new node with item in its data, insert into the BST
    (*current)->parent = prev;                   //Assign the prev node to the new node's parent;
     isize++;
     
     return true;
  }

  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use >, <=, >=)
   */ // TODO
  iterator find(const Data& item) const {
    BSTNode<Data>* current = root;
    
    /*Traverse the BST to find the item*/
    while(current != NULL && current->data != item){
      if (item < current->data ){
        current = current->left;
      }else{
        current = current->right;
      }
    }
    
    return typename BST<Data>::iterator(current);  //Return an iterator pointing to the item
  }

  
  /** Return the number of items currently in the BST.
   */ // TODO
  unsigned int size() const {
    return isize;
  }

  /** Return true if the BST is empty, else false.
   */ // TODO
  bool empty() const {
    if (isize == 0){
      return true;
    }else{
      return false;
    }
  }

  /** Return an iterator pointing to the first item in the BST (not the root).
   */ // TODO
  iterator begin() const {
    return typename BST<Data>::iterator(BST<Data>::first(root));   //Return an iterator pointing to the left-most item in the BST
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(0);
  }

  /** Perform an inorder traversal of this BST.
   */
  void inorder() const {
    inorder(root);
  }


private:

  /** Recursive inorder traversal 'helper' function */

  /** Inorder traverse BST, print out the data of each node in ascending order.
      Implementing inorder and deleteAll base on the pseudo code is an easy way to get started.
   */ // TODO
  void inorder(BSTNode<Data>* n) const {
    /* Pseudo Code:
      if current node is null: return;
      recursively traverse left sub-tree
      print current node data
      recursively traverse right sub-tree
    */
    if (n == NULL){
      return;
    }
    inorder(n->left);
    std::cout << *n << std::endl;
    inorder(n->right);
  }

  /** Find the first element of the BST
   */ 
  static BSTNode<Data>* first(BSTNode<Data>* root) {
    if(root == 0) return 0;
    while(root->left != 0) root = root->left;
    return root;
  }

  /** do a postorder traversal, deleting nodes
   */ // TODO
  static void deleteAll(BSTNode<Data>* n) {
    /* Pseudo Code:
      if current node is null: return;
      recursively delete left sub-tree
      recursively delete right sub-tree
      delete current node
    */
    if (n == NULL){
      return;
    }
    deleteAll(n->left);
    deleteAll(n->right);
    delete n;
  }
  
  /** do a postorder traversal just like deleteAll
      set each node's left, right and parent pointer to NULL 
      delete each node.
      This helper method is designed to deal with the problem of setting pointer of each node to NULL 
   */  
  static void deleteHelper(BSTNode<Data>* node){
    if (node != NULL){
      deleteHelper(node->left);
      node->left = NULL;
      deleteHelper(node->right);
      node->right = NULL;
      
      node->parent = NULL;
      delete node;
    }
    return;
  }
 };


#endif //BST_HPP
