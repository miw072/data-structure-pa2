#ifndef RST_HPP
#define RST_HPP
#include "BST.hpp"
#include <iostream>
#include <stdlib.h>

using namespace std;

template <typename Data>
class RST : public BST<Data> {

public:

  /* Insert new data into the RST if it is not already present.
   * Input
   *    item - the data to insert.
   *    return - true if the item was inserted. If the item was already contained in
   *       the tree then return false.
   */ 
  virtual bool insert(const Data& item) {
    
    // TODO: Implement this function!
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
    (*current)->parent = prev;                   //Assign the prev node to the new node's parent
    (*current)->priority = rand();               //set random priority to the new node
    
    this->isize++;
    
    while((*current)->parent != NULL && (*current)->priority > (*current)->parent->priority){
        if ((*current)->parent->left == (*current)){
          rotateRight((*current)->parent, (*current));
        }else{
          rotateLeft((*current)->parent, (*current));
        }
    }
    return true;
  }

private:

  /* Perform a 'right rotation' that changes the structure of the tree without
   * interfering with the size, data content, and left->right order of nodes in the RST.
   * This rotation is done by changing the 'left', 'right', and/or 'parent' pointers
   * of a subset of nodes without changing their 'priority' values.
   *
   * Input
   *    par - a parent node in the RST with a left child
   *    child - the left child of 'par'
   *
   * Output
   *   The resulting tree will have 'par' and 'child' in the same order but switched
   *   in level, meaning 'par' will effectively become the right-child of 'child'.
   *
   */
  void rotateRight( BSTNode<Data>* par, BSTNode<Data>* child ) {
    
    // TODO: Implement this function!
    if (par == this->root){
      child->parent = NULL;
      this->root = child; 
      
      par->left = child->right;
      if (child->right != NULL){
        child->right->parent = par;
      }
      
      par->parent = child;
      child->right = par; 
    }
    else{
      if (par->parent->left == par){
        par->parent->left = child;
      }else{
        par->parent->right = child;
      }
      child->parent = par->parent;

      par->left = child->right;
      if (child->right != NULL){
        child->right->parent = par;
      }
      
      par->parent = child;
      child->right = par;
    }
    
  }

  
  /* Perform a 'left rotation' that changes the structure of the tree without
   * interfering with the size, data content, and left->right order of nodes in the RST.
   * This rotation is done by changing the 'left', 'right', and/or 'parent' pointers
   * of a subset of nodes without changing their 'priority' values.
   *
   * Input
   *    par - a parent node in the RST with a right child
   *    child - the right child of 'par'
   *
   * Output
   *   The resulting tree will have 'par' and 'child' in the same order but switched
   *   in level, meaning 'par' will effectively become the left-child of 'child'.
   *
   */
  void rotateLeft( BSTNode<Data>* par, BSTNode<Data>* child )
  {
    
    // TODO: Implement this function!
    if (par == this->root){
      child->parent = NULL;
      this->root = child; 
      
      par->right = child->left;
      if (child->left != NULL){
        child->left->parent = par;
      }
      
      par->parent = child;
      child->left = par; 
    }
    else{
      if (par->parent->left == par){
        par->parent->left = child;
      }else{
        par->parent->right = child;
      }
      child->parent = par->parent;

      par->right = child->left;
      if (child->right != NULL){
        child->left->parent = par;
      }
      
      par->parent = child;
      child->left = par;
    }
  }

public:

  /* THIS FUNCTION IS USED FOR TESTING, DO NOT MODIFY
   * 
   * Calls BST::insert so we can add data to test rotateRight and rotateLeft before
   * implementing the fully correct version of RST::insert.
   * 
   */
  bool BSTinsert(const Data& item) {
    
    return BST<Data>::insert(item);
    
  }
  
  /* THIS FUNCTION IS USED FOR TESTING, DO NOT MODIFY
   * 
   * Locates the node for an item and rotates it left or right without changing the
   * left->right order of nodes in the RST
   * Input
   *    item - the Data item to rotate.
   *    leftOrRight - if true then rotateLeft, otherwise rotateRight
   *    output - 0 if item could be found and had a child to rotate with, 1 if not. -1 if
   *         rotation failed for other reasons
   */
  int findAndRotate(const Data& item, bool leftOrRight) {
    
     BSTNode<Data>* current = RST<Data>::root;
     while ( current != 0 ) {
       if ( item < current->data ) {
         current = current->left;
       }
       else if ( current->data < item ) {
         current = current->right;
       }
       else {  // already in the tree
         break;
       }
     }
     
     if (current == 0 or current->data != item) {
       return 1;
     }
     
     if (leftOrRight) {
       if (current->right == 0) {
         return 1;
       }
       BSTNode<Data>* right = current->right;
       rotateLeft(current, current->right);
       
       // make sure we actually do a rotation
       if (current->right == right) {
         return -1;
       }
       
     } else {
       if (current->left == 0) {
         return 1;
       }
       BSTNode<Data>* left = current->left;
       rotateRight(current, current->left);
       
       // make sure we actually do a rotation
       if (current->left == left) {
         return -1;
       }
     }
     return 0;
  }
};
#endif // RST_HPP
