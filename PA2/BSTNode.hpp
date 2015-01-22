/**
 *Author: Mingxuan Wang
 *PID: A53077257
 */
#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>

template<typename Data>
class BSTNode {

public:

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d) : data(d) {
    left = right = parent = 0;
  }

  BSTNode<Data>* left;
  BSTNode<Data>* right;
  BSTNode<Data>* parent;
  Data const data;   // the const Data in this node.
  int priority;      // the priority used for treap

  /** Return the successor of this BSTNode in a BST, or 0 if none.
   ** PRECONDITION: this BSTNode is a node in a BST.
   ** POSTCONDITION:  the BST is unchanged.
   ** RETURNS: the BSTNode that is the successor of this BSTNode,
   ** or 0 if there is none.
   */ // TODO
  BSTNode<Data>* successor() {
    if (right != NULL){                        //If right child is not NULL, find leftmost descendant of the right child
      BSTNode<Data>* leftmost = right;
      while(leftmost->left != NULL){
        leftmost = leftmost->left;
      } 
      return leftmost;
    }else{                                     //If right child is NULL, the successor must be somewhere above this node
      if (parent == NULL){                     //If this node is the root, return NULL
        return NULL;
      }else if (this == parent->left){         //If this node is its parent's left child, its successor is its parent
        return parent;
      }else{                                   //If none of above, trace up to the root or the first node which the previous tracing node is its left child
        BSTNode<Data>* trackerParent = parent->parent;
        BSTNode<Data>* tracker = parent;
        
        while (trackerParent != NULL && tracker == trackerParent->right){
          tracker = trackerParent;
          trackerParent = trackerParent->parent;
        }
        return trackerParent;
      }
    }
  }

}; 

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
