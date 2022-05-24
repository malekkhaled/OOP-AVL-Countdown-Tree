#ifndef __COUNTDOWN_TREE_H
#define __COUNTDOWN_TREE_H

#include <iostream>
using namespace std;

class Node;
class CountdownTree;

class Node
{
  friend CountdownTree;
  friend ostream& operator<<(ostream&, const Node*);
private:
  int data;
  int height;
  Node* parent;
  Node* left;
  Node* right;
public:
  //Provided:  constructs a leaf node with the given value
  Node(int d) { data = d; height = 1; parent = left = right = nullptr; }

  //Optional:  returns a pointer to the Node with the given value
  Node* search(int);
  //Optional:  same as above, but as an accessor
  const Node* search(int) const;
  
  //Optional:  returns a pointer to the Node with the largest or smallest value in this subtree
  Node* max();
  Node* min();

  //Optional:  adds a Node with the given value to the subtree rooted at this node
  void insert(int);

  //Optional:  removes this Node from the tree and frees it
  //Returns the root of the subtree that remains
  // (useful if we are deleting the root)
  Node* remove();

  //Optional:  calculates the height of this Node based on its children
  void updateHeight();

  //Required:  recursively restores the balance of the tree
  //See project description for more details on this process
  void rebalance();

  //Optional:  rotates this Node left or right
  void rotateLeft();
  void rotateRight();

  //Optional:  returns whether or not this Node is a left or right child of its parent
  bool isLeftChild() const;
  bool isRightChild() const;

  //Provided:  validates that the CountdownTree is correct
  void validate(int&) const;

  //Provided:  recursive destructor
  //Make sure left = right = null if you don't want to delete 
  //the entire subtree rooted at this node
  ~Node() { delete left; delete right; }
};

class CountdownTree
{
  friend ostream& operator<<(ostream&, const CountdownTree&);
  static const int MINIMUM_COUNTDOWN = 10;
private:
  Node* root;
  int size;
  int count;
public:
  //Provided:  constructs and empty tree
  CountdownTree() 
    { root = nullptr; size = 0; 
      count = MINIMUM_COUNTDOWN; }

  //Required:  adds or removes the given value to the tree
  void insert(int);
  void remove(int);

  //Required:  returns whether the tree contains the given value
  bool contains(int) const;

  //Optional:  decrements the countdown and rebalances the tree
  void countdown();

  //Provided:  gets the height of the tree
  int getHeight() const;

  //Provided:  validates that the tree is valid
  //Call this immediately after rebalancing
  void validate() const;

  //Provided:  returns the countdown count
  int getCount() const { return count; }
  //Provided:  returns the size of the tree
  int getSize() const { return size; }
  //Provided:  recursively destroys the tree
  ~CountdownTree() { delete root; }
};

//Provided:  recursively prints the CountdownTree contents
ostream& operator<<(ostream&, const CountdownTree&);
ostream& operator<<(ostream&, const Node*);

#endif