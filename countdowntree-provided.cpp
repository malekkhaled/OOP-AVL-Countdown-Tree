#include "countdowntree.h"

//Returns the height of this tree
int CountdownTree::getHeight() const
{
  if (root != nullptr)
    return root->height; 
  else
    return 0;
}

//Validates that the size, parent pointers, heights, and
//BST property are all correct
void CountdownTree::validate() const
{
  int tempSize = 0;
  if (root != nullptr)
    root->validate(tempSize);

  if (size != tempSize)
    cout << "Number of nodes (" << tempSize << ") doesn't match size (" << size << ")\n";
}

//Recursively validates the height, parent pointers, and
//BST property in the subtree rooted at this node
//Accumulates the number of nodes in the subtree to size
void Node::validate(int& size) const
{
  //Count this node
  size++;

  //Validate height
  if (left == nullptr && right == nullptr)
  {
    if (height != 1)
      cout << "Height of " << data << " = " << height << " (leaf)\n";
  }
  else if (right == nullptr)
  {
    if (height != left->height + 1)
      cout << "Height of " << data << " = " << height << " (child height = " << left->height << ")\n";
  }
  else if (left == nullptr)
  {
    if (height != right->height + 1)
      cout << "Height of " << data << " = " << height << " (child height = " << right->height << ")\n";
  }
  else if (left->height >= right->height)
  {
    if (height != left->height + 1)
      cout << "Height of " << data << " = " << height << " (children:  " << left->height << " and " << right->height << ")\n";
  }
  else if (height != right->height + 1)
    cout << "Height of " << data << " = " << height << " (children:  " << left->height << " and " << right->height << ")\n";

  //Validate BST property and child <-> parent pointers
  //Validate left and right subtrees recursively
  if (left != nullptr)
  {
    if (left->data > data)
      cout << "Left child of " << data << " has value " << left->data << '\n';
    if (left->parent != this)
      cout << "Parent pointer for " << left->data << " not set to " << data << '\n';
    left->validate(size);
  }
  if (right != nullptr)
  {
    if (right->data < data)
      cout << "Right child of " << data << " has value " << right->data << '\n';
    if (right->parent != this)
      cout << "Parent pointer for " << right->data << " not set to " << data << '\n';
    right->validate(size);
  }
}

//Print all nodes in the CountdownTree
ostream& operator<<(ostream& out, const CountdownTree& tree)
{
  return out << tree.root;
}

//Recursively print the subtree rooted at this node
//Format:  (data [height] L=left_subtree R=right_subtree)
ostream& operator<<(ostream& out, const Node* node)
{
  if (node != nullptr)
    return out << '(' << node->data 
               << " [" << node->height 
               << "] L=" << node->left 
               << " R=" << node->right << ')';
  else
    return out;
}

// Author: William Hendrix

/*Rotate this node (*) left
    G             G
    |             |
    P             *
   / \           / \
  X   *  ===>   P   Z
     / \       / \  
    Y   Z     X   Y
  Fails if parent is null or this node is a left child
//*/

void Node :: rotateLeft()
{
    //P->right = Y
  if (parent != nullptr)
    parent->right = left;
  //Y->parent = P
  if (left != nullptr)
    left->parent = parent;
  //left = P
  left = parent;
  //parent = G
  parent = parent->parent;
  //G->child = this
  if (left->isLeftChild())
    parent->left = this;
  else if (left->isRightChild())
    parent->right = this;
  //P->parent = this
  left->parent = this;
}

// Author: William Hendrix

/*Rotate this node (*) right
    P           *
   / \         / \
  *   Z  ===> X   P
 / \             / \ 
X   Y           Y   Z
//*/

void Node :: rotateRight()
{
  if (parent != nullptr)
    parent->left = right;

  if (right != nullptr)
    right->parent = parent;

  right = parent;
  parent = parent->parent;

  if (right->isLeftChild())
    parent->left = this;
  else if (right->isRightChild())
    parent->right = this;

  right->parent = this;
}

// Author: William Hendrix

//Returns whether this node is a left child
//Returns false for root
bool Node::isLeftChild() const
{
  return parent != nullptr && parent->left == this;
}

// Author: William Hendrix

//Returns whether this node is a right child
//Returns false for root
bool Node::isRightChild() const
{
  return parent != nullptr && parent->right == this;
}

// Author: William Hendrix

//Returns whether the BST contains a given value
//Recursive unless BST is empty
bool CountdownTree :: contains(int x) const
{
  if (root == nullptr)
    return false;
  else if (root->search(x) != nullptr)
    return true;
  else
    return false;
}

// Author: William Hendrix

//Recursive search function
//Returns nullptr if not found
Node* Node::search(int x)
{
  if (x == data)
    return this;
  else if (x < data)
  {
    if (left == nullptr)
      return nullptr;
    else
      return left->search(x);
  }
  else
  {
    if (right == nullptr)
      return nullptr;
    else
      return right->search(x);
  }
}

// Author: William Hendrix

//Insert an element into the BST
//Works recursively unless BST is empty
void CountdownTree :: insert(int x)
{
  if (size == 0)
  {
    root = new Node(x);
    root->updateHeight();
  }
  else
    root->insert(x);
  size++;
  countdown();
}

// Author: William Hendrix

//Recursive insertion function
//Inserts a BSTNode with x below this node
void Node::insert(int x)
{
  if (x < data)
  {
    if (left != nullptr)
      left->insert(x);
    else
    {
      left = new Node(x);
      left->parent = this;
    }
  }
  else
  {
    if (right != nullptr)
      right->insert(x);
    else
    {
      right = new Node(x);
      right->parent = this;
    }
  }
}

// Author: William Hendrix

//Function to remove a value from the BST
void CountdownTree::remove(int x)
{
  if (root == nullptr)
    return; //empty BST
  
  Node* victim = root->search(x);
  if (victim == nullptr)
    return; //doesn't contain x
  
  if (victim == root) //update root if deleting
    root = victim->remove(); 
  else
    victim->remove();

  countdown();
}

// Author: William Hendrix

//Function to remove this node from its BST
Node* Node::remove()
{
  int numChildren = (left != nullptr) + (right != nullptr);

  cout << "numChildren: " << numChildren << endl;

  Node* temp = parent;

  if (numChildren == 0)
  {
    if (isLeftChild()) //if this is a left child
      parent->left = nullptr;
    else if (isRightChild())
      parent->right = nullptr;
    //don't dereference parent if root

    delete this;
    return nullptr; //root = nullptr if deleting root
  }
  else if (numChildren == 1)
  {
    Node* child;
    if (left != nullptr)
      child = left;
    else
      child = right;
    
    //Point child to parent
    child->parent = parent;

    //Point parent to child
    if (isLeftChild())
      parent->left = child;
    else if (isRightChild())
      parent->right = child;
    
    left = right = nullptr; //important so we don't delete child
    delete this;
    return child; //root = child if deleting root
  }
  else //2 children
  {
    Node* swap = left-> max();
    data = swap->data;
    swap->remove(); //recursively delete other node
    return this; //root pointer doesn't move
  }
  parent -> updateHeight();
}

// Author: William Hendrix

//Recursive function to find the min node below this one
Node* Node:: min()
{
  if (left == nullptr)
    return this;
  else
    return left-> min();
}

// Author: William Hendrix

//Recursive function to find the max node below this one
Node* Node:: max()
{
  if (right == nullptr)
    return this;
  else
    return right-> max();
}

void Node:: updateHeight()
{
  int lht = 1, rht = 1;
  
  if (left != nullptr)
    lht = left -> height +1;
  
  if (right != nullptr)
    rht = right -> height + 1;
  
  if (lht > rht)
    height = lht;
  else
    height = rht;
}



void CountdownTree:: countdown()
{
  count--;
  if(count == 0)
  {
    root->rebalance();

    while (root -> parent != nullptr)
      root = root -> parent;

    if (getHeight() > 10)
      count = getHeight();
    else  
      count = 10;
  }
}

void Node :: rebalance()
{
  if (left != nullptr)
    left -> rebalance();
  
  if (right != nullptr)
    right -> rebalance();

  int balance;

  if(right != nullptr && left != nullptr)
     balance= (right->height) - (left -> height);
  else if(left != nullptr && right == nullptr)
    balance =  - (left -> height);
  else if (left == nullptr && right != nullptr)
    balance= (right->height);
  else 
    balance = 0;

  if (balance <= -2)
  {
    int bal;
    if (left -> right == nullptr)
      if (left -> left == nullptr)
        bal = 0;
      else 
        bal = 0 - (left -> left -> height);

    if (left-> right != nullptr)
      if(left-> left != nullptr)
        bal = (left-> right -> height) - (left -> left -> height);
      else  
        bal = left -> right -> height;


    if (bal <= 0)
    {
      left -> rotateRight();
      this ->  updateHeight();
      parent -> updateHeight();
    }

    if (bal > 0)
    {
      left -> right -> rotateLeft();
      left  -> rotateRight();
      this -> updateHeight();
      parent -> left -> updateHeight();
      parent -> updateHeight();
    }
  }

  else if (balance >= 2)
  {
    int bal;
    if (right -> right == nullptr)
      if (right -> left == nullptr)
        bal = 0;
      else 
        bal = 0 - right -> left -> height;
    
    if (right -> right != nullptr)
      if (right -> left == nullptr)
        bal = right-> right -> height;
      else 
        bal = right -> right -> height - right -> left -> height;

    if (bal < 0)
    {
      right -> left -> rotateRight();
      right -> rotateLeft();
      parent -> right -> updateHeight();
      this -> updateHeight();
      parent -> updateHeight();
    }

    if (bal >= 0)
    {
      right -> rotateLeft();
      this -> updateHeight();
      parent -> updateHeight();
    }
  }
  else
    this -> updateHeight();
}