#include "RST.hpp"
#include "countint.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

// random generator function:
int myrandom (int i) { return rand()%i;}

int test_RST_rotate(int N) {
  
  cout << endl << "### Testing RST rotateLeft and rotateRight functionality ..." << endl << endl;
  
  /* Create an STL vector of some countints, in sorted order */
  vector<countint> v;
  vector<countint> v_sorted;
  for(int i=0; i<N; i++) {
    //    v.push_back(i);
    v.push_back(i);
    v_sorted.push_back(i);
  }
  
  // Create a reproducible psuedo-random insertion order
  srand ( unsigned ( 149 ) );
  std::random_shuffle ( v.begin(), v.end(), myrandom);

  /* Create an empty instance of RST holding countint */
  RST<countint> r = RST<countint>();

  /* Insert the data items, in order */
  cout << "Inserting " << N << " random keys in initially empty RST...";
  vector<countint>::iterator vit = v.begin();
  vector<countint>::iterator ven = v.end();
  for(; vit != ven; ++vit) {
    // all these inserts are unique, so should return true
    if(! r.BSTinsert(*vit) ) {
      cout << endl << "Incorrect return value when inserting " << *vit << endl;
      return -1;
    }
  }
  cout << " done." << endl;
  
  cout << "Rotating an arbitrary node with rotateLeft... ";
  vit = v.begin();
  ven = v.end();
  for(; vit != ven; ++vit) {
    int ret = r.findAndRotate(*vit, true);
    if (ret == 0)
    {
      break;
    } else if (ret < 0)
    {
      cout << endl << "Failed to rotate node " << *vit << endl;
      return -1;
    }
  }
  
  //  r.inorder();
  
  /* Test iterator; should iterate the entire tree inorder */
  cout << "Checking traversal using iterator...";
  vit = v_sorted.begin();
  BST<countint>::iterator en = r.end();
  BST<countint>::iterator it = r.begin();
  int i = 0;
  for(; it != en; ++it) {
    //    cout << *it << endl;
    if(*it != *vit) {
      cout << endl << "Incorrect inorder iteration of RST." << endl;
      return -1;
    }
    ++i;
    ++vit;
  }
  if(i!=N) {
    cout << endl << "Early termination during inorder iteration of RST." << endl;
    return -1;
  }
  cout << " OK." << endl;
  
  cout << "Rotating an arbitrary node with rotateRight... ";
  vit = v.begin();
  ven = v.end();
  for(; vit != ven; ++vit) {
    int ret = r.findAndRotate(*vit, false);
    if (ret == 0)
    {
      break;
    } else if (ret < 0)
    {
      cout << endl << "Failed to rotate node " << *vit << endl;
      return -1;
    }
  }
  
  //  r.inorder();
  
  /* Test iterator; should iterate the entire tree inorder */
  cout << "Checking traversal using iterator...";
  vit = v_sorted.begin();
  en = r.end();
  it = r.begin();
  i = 0;
  for(; it != en; ++it) {
    //    cout << *it << endl;
    if(*it != *vit) {
      cout << endl << "Incorrect inorder iteration of RST." << endl;
      return -1;
    }
    ++i;
    ++vit;
  }
  if(i!=N) {
    cout << endl << "Early termination during inorder iteration of RST." << endl;
    return -1;
  }
  cout << " OK." << endl;

  cout << endl << "### ROTATION TESTS PASSED ####" << endl << endl;
  
  return 0;
}

int test_RST_insert(int N) {

  cout << "### Testing RST insert functionality ..." << endl << endl;
  
  double  maxcompsperkey =  (log(N) * 2.5); 

  /* Create an STL vector of some countints, in sorted order */
  vector<countint> v;
  for(int i=0; i<N; i++) {
    //    v.push_back(i);
    v.push_back(i);
  }

  /* Create an empty instance of RST holding countint */
  RST<countint> r = RST<countint>();

  /* Clear the comparison counter */
  countint::clearcount();

  /* Insert the data items, in order */
  cout << "Inserting " << N << " sorted keys in initially empty RST...";
  vector<countint>::iterator vit = v.begin();
  vector<countint>::iterator ven = v.end();
  for(; vit != ven; ++vit) {
    // all these inserts are unique, so should return true
    if(! r.insert(*vit) ) {
      cout << endl << "Incorrect return value when inserting " << *vit << endl;
      return -1;
    }
  }
  cout << " done." << endl;
  
  //  r.inorder();
  
  /* Test iterator; should iterate the entire tree inorder */
  cout << "Checking traversal using iterator...";
  vit = v.begin();
  BST<countint>::iterator en = r.end();
  BST<countint>::iterator it = r.begin();
  int i = 0;
  for(; it != en; ++it) {
    //    cout << *it << endl;
    if(*it != *vit) {
      cout << endl << "Incorrect inorder iteration of RST." << endl;
      return -1;
    }
    ++i;
    ++vit;
  }
  if(i!=N) {
    cout << endl << "Early termination during inorder iteration of RST." << endl;
    return -1;
  }
  cout << " OK." << endl;

  /* How many comparisons did it take to do the inserts, avg per key? */
  double compsperkey =  countint::getcount() / (double) N;
  cout << "That took " << compsperkey << " average comparisons per key, ";
  if(compsperkey <= maxcompsperkey) cout << "OK. " << endl;
  else if (compsperkey <= maxcompsperkey * 2) cout << "could be better... max is " << maxcompsperkey << endl;
  else {
    cout << "way too many!" << endl;
    return -1;
  }

  /* Test iterator; should iterate the entire tree inorder */
  cout << "Checking traversal using iterator...";
  vit = v.begin();
  en = r.end();
  it = r.begin();
  i = 0;
  for(; it != en; ++it) {
    //    cout << *it << endl;
    if(*it != *vit) {
      cout << endl << "Incorrect inorder iteration of RST." << endl;
      return -1;
    }
    ++i;
    ++vit;
  }
  if(i!=N) {
    cout << endl << "Early termination during inorder iteration of RST." << endl;
    return -1;
  }
  cout << " OK." << endl;
  
  cout << endl << "### INSERTION TESTS PASSED ####" << endl << endl;
  
  return 0;
}

/**
 * A simple partial test driver for the RST class template.
 * P2 CSE 100
 * Author: P. Kube (c) 2010, 2011, 2012
 */
int main(int argc, char** argv) {

  int N = 1000;
  if(argc > 1) N = atoi(argv[1]);
  // a good RST implementation should need no more than this number
  // of key comparisons when inserting N keys
  
  int return_value = test_RST_rotate(N);
  
  if (return_value != 0) {
    return return_value;
  }
  
  return test_RST_insert(N);
}
