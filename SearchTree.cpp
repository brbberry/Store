// Blake Berry
// 01/10/2022
// Homework 1
// This file is an implimentation of the SearchTree class. The search tree 
// contains node structures that hold a pointer to a comparable object and 
// pointers to left and right children.
//------------------------------------------------------------------------------

#include "SearchTree.h"


//-------------------------- Default Constructor ------------------------------
// Creates a default search tree
// Postconditions: a search tree with a null root pointer is created
SearchTree::SearchTree() :
   root_(nullptr)
{
}


//-------------------------- copy ----------------------------------------
// Recursively creates a deep copy of a tree from the root node passed in
// A pointer to the deep copied root node for the tree copied is returned
// Preconditions:   The root of the tree passed in must be defined
// Postconditions:  A pointer to the deep copied root node for the tree 
//                  copied is returned
SearchTree::STNode* SearchTree::copy(STNode* root) const
{
   if (root == nullptr) {
      return nullptr;
   }

   STNode* toAdd = new STNode();
   toAdd->left_ = copy(root->left_);
   toAdd->right_ = copy(root->right_);
   toAdd->count_ = root->count_;
   toAdd->held_ = root->held_->copy();
   return toAdd;
}


//-------------------------- Copy Constructor ---------------------------------
// creates a new tree that is a deep copy of a given tree
// Preconditions : The tree to be copied must be defined
// Postconditions: creates a new tree that is a deep copy of the one passed in
// Function Calls: copy, the recursive helper function that creates the deep 
//                 copy
SearchTree::SearchTree(const SearchTree& toCopy) :
   root_(nullptr)
{

   root_ = copy(toCopy.root_);
}


//-------------------------- EmptyTreeHelper ----------------------------------
// Recursively traverses a search tree post order freeing the memeory 
// associated with a given nodes right and left subtrees and resets the root 
// node
// Preconditions : The root of the calling tree must be passed in if the tree
//                 is to be emptied
// Postconditions: the left and right subtrees of the root will be freed of 
//                 memory and the root node of the calling tree will be reset
void SearchTree::emptyTreeHelper(STNode*& root)
{
   if (root == nullptr) {
      return;
   }

   emptyTreeHelper(root->left_);
   emptyTreeHelper(root->right_);

   // if we are not at the calling trees root, free the memory completely
   if (root != root_) {
      const Comparable* compToDel = root->held_;
      STNode* nodeToDel = root;
      root->held_ = nullptr;
      root = nullptr;
      delete compToDel;
      delete nodeToDel;
   }
   // if we are at the calling tree's root, just free the held and
   // reset the count
   else {
      delete root->held_;
      root->held_ = nullptr;
      root->count_ = 0;
   }
   return;
}


//-------------------------- makeEmpty ---------------------------------------
// Removes all the nodes in a given tree, reseting the tree to its intial
// state after default construction
// Postconditions: free's the memeory associated the the trees nodes. The
//                 root node is set to nullptr
// Function Calls: emptyTreeHelper() to recursively free the memory
void SearchTree::makeEmpty()
{
   emptyTreeHelper(root_);
   return;
}


//-------------------------- Destructor ---------------------------------------
// Frees the memeory associated with a given tree
// Postconditions: The memory associated with the calling tree is completely
//                 free'd. The "tree" after the destrucotr is called is not
//                 usable
// Function Calls: makeEmpty() to free all the memory associated with the tree
//                 except the root
SearchTree::~SearchTree()
{
   makeEmpty();
   delete root_;
   root_ = nullptr;
}


//-------------------------- operator= ---------------------------------------
// Assigns a given tree to the calling tree. A deep copy is made of the passed
// in tree, seen on the rhs of =
// Preconditions : The tree on the right must be defined
// Postconditions: If the tree on the right is not the same as the calling tree
//                 a deep copy is made and assigned to the calling tree. If the
//                 rhs is the calling tree then it returns itself
// Function Calls: emptyTreeHelper() to free the memory associated with the 
//                 calling tree
//                 copy() to make a deep copy of the rhs tree
const SearchTree& SearchTree::operator=(const SearchTree& right)
{
   if (this != &right) {
      emptyTreeHelper(root_);
      root_ = copy(right.root_);
   }

   return *this;
}


//-------------------------- TwoTreeTraverse ----------------------------------
// Recursively traverses two trees in preorder checking to see if each tree
// holds the same comparable with the same count at each node
// Preconditions : The root of both trees must be input to ensure each tree
//                 is checked 1:1
// Postconditions: True is returned if the trees are equal and false is
//                 returned otherwise
bool SearchTree::twoTreeTraverse(STNode* firstRoot, STNode* secondRoot) const
{

   if (firstRoot == nullptr && secondRoot == nullptr) {
      return true;
   }
   // if one tree node is null and the other isnt 
   else if ((firstRoot == nullptr && secondRoot != nullptr) ||
      (secondRoot == nullptr && firstRoot != nullptr)) {

      return false;
   }
   // if their counts do not match
   else if (firstRoot->count_ != secondRoot->count_) {
      return false;
   }
   // if the hold different comparables
   else if (*firstRoot->held_ != *secondRoot->held_) {
      return false;
   }
   else {
      bool equal = (twoTreeTraverse(firstRoot->left_, secondRoot->left_)) &&
         (twoTreeTraverse(firstRoot->right_, secondRoot->right_));

      return equal;
   }
}


//-------------------------- operator== ---------------------------------------
// Checks if two trees are equivilent. Equivilance is defined as each tree 
// storing the same comparable in the same location and with the same count
// as the other.
// Postconditions: Returns true if both trees are equivilent
//                 Returns false if the trees are not equivilent.
// Function Calls: twoTreeTraverse is used traverse both trees to check for
//                 equivilance
bool SearchTree::operator==(const SearchTree& right) const
{
   return twoTreeTraverse(root_, right.root_);
}


//-------------------------- operator!= ---------------------------------------
// Checks if two trees are not equivilent. Equivilance is defined as each tree 
// storing the same comparable in the same location and with the same count
// as the other.
// Postconditions: Returns true if both trees are not equivilent
//                 Returns false if the trees are equivilent.
// Function Calls: operator== is used to determine if they are equal
bool SearchTree::operator!=(const SearchTree& right) const
{
   return !(*this == right);
}


//-------------------------- InsertHelper -------------------------------------
// Recrusivly searches the tree to find the node in which a given comparable
// will be inserted to ensure that binary search tree properties are maintained
// That is the comparables in the left children will be less than the parent
// node and those on the right will be greater
// Preconditions :  The root of the tree must be passed in to ensure that 
//                  proper order is maintained
// Postconditions:  Returns a pointer to the node in which a node holding
//                  the given comparable should be stored. If the tree has no
//                  root node, nullptr is returned
SearchTree::STNode* SearchTree::insertHelper(STNode* root,
   const Comparable& toFind) const
{
   if (root == nullptr) {
      return nullptr;
   }

   // search tree for insert position
   if (*root->held_ < toFind) {
      // if found
      if (root->right_ == nullptr) {
         return root;
      }
      else {
         return insertHelper(root->right_, toFind);
      }
   }
   else if (*root->held_ > toFind) {
      // if found
      if (root->left_ == nullptr) {
         return root;
      }
      else {
         return insertHelper(root->left_, toFind);
      }
   }
   // return if they are equal
   else {
      return root;
   }
}


//-------------------------- Insert ------------------------------------------
// Inserts a comparable into the search tree, if it is not already present.
// If the comprable is present its count is increased.
// Postconditions: If the comparable can be inserted into the tree it is
//                 inserted maintaing SearchTree properties and true is
//                 returned. If it is already in the tree, the count of that
//                 comparable is increased. False is returned
// Function Calls: InsertHelper() is called to return a pointer to the proper
//                 insert location
bool SearchTree::insert(const Comparable* toInsert)
{

   if (toInsert == nullptr) {
      return false;
   }

   STNode* insertHere = insertHelper(root_, *toInsert);

   // nullptr is only returned if the root is empty
   if (insertHere == nullptr) {
      root_ = new STNode();
      root_->count_ = 1;
      root_->held_ = toInsert;
   }
   // if the comparable is already in the tree
   else if (*insertHere->held_ == *toInsert) {
      insertHere->count_++;
      return false;
   }
   // we have to insert on the left
   else if (*insertHere->held_ > *toInsert) {

      STNode* toAdd = new STNode();
      toAdd->count_ = 1;
      toAdd->held_ = toInsert;
      insertHere->left_ = toAdd;
   }
   // we have to insert on the right
   else {
      STNode* toAdd = new STNode();
      toAdd->count_ = 1;
      toAdd->held_ = toInsert;
      insertHere->right_ = toAdd;
   }

   return true;
}


//-------------------------- DeleteNode ---------------------------------------
// Recursively traverses a given tree searching for a comparable. If found
// the count is decreased or the node is deleted from the tree. Search tree 
// properties are maintained after a node is deleted
// Preconditions : The root node refrence must be the root pointer of the 
//                 calling tree
// Postconditions: Decreases the occurence count of a given comparable if it
//                 is found in the tree, and deletes the node storing the
//                 comparable if the count reaches 0. True is returned. If 
//                 the comparable is not found false is returned.
// Function Calls: DeleteRoot() to delete the tree node holding the found
//                 comparable if there is only one instance of that comparable
bool SearchTree::deleteNode(STNode*& root, const Comparable& toDel)
{
   if (root == nullptr) {
      return false;
   }

   // recursively search for a node to delete
   else if (*root->held_ == toDel) {

      // adding this in bc we dont want engative inventories
      // meaning the count is already 0
      if (root->count_ == 0) {
         return false;
      }
      else {
         root->count_--;
      }

      if (root->count_ == 0) {
         // commenting this out so that it just says the inv is zero
         //deleteRoot(root);
      }
      return true;
   }
   else if (*root->held_ > toDel) {
      return deleteNode(root->left_, toDel);
   }
   else {
      return deleteNode(root->right_, toDel);
   }
}


//-------------------------- DeleteRoot ---------------------------------------
// Frees the memeory associated with a given node in the tree, including that 
// of the comparable it holds. The children of the root being deleted are 
// managed to ensure that the proper Search Tree Properties are upheld
// Preconditions : The root to be deleted must exist and should have a count
//                 of 0.
// Postconditions: If the root to be deleted is a leaf, the memory is freed
//                 If the root to be deleted has one child, that child is 
//                 adopted by the parent of the deleted root
//                 If the root to be deleted has two children the tree is 
//                 traversed and the root is replaced with the node holding
//                 the next greatest comparable
// Function Calls: getAndDeleteNextGreatest() is used to get the node with
//                 the next greatest value from the node being deleted.
void SearchTree::deleteRoot(STNode*& root)
{

   delete root->held_;
   root->held_ = nullptr;

   //if root is a leaf node
   if (root == nullptr) {
      return;
   }

   // either the root is a leaf or has one child
   if (root->left_ == nullptr || root->right_ == nullptr) {
      STNode* toDel = root;
      root = root->left_ == nullptr ? root->right_ : root->left_;
      delete toDel;
      toDel = nullptr;
   }
   // the root has two children
   else {
      STNode* toFill = getNextGreatest(root->right_);
      root->count_ = toFill->count_;
      root->right_ = toFill->right_;
      root->held_ = toFill->held_;
      delete toFill;
      toFill = nullptr;
   }
}


//----------------------- getAndDeleteNextGreatest ----------------------------
// Given a node, a pointer to a node holding the next greatest comparable is
// returned.
// Preconditions:   The right child of the root to be deleted must be passed in
// Postconditions:  The node with the next greatest comparable is found copied 
//                  and returned.
SearchTree::STNode* SearchTree::getNextGreatest(STNode*& root)
{
   if (root->left_ == nullptr) {

      STNode* copy = root;
      root = nullptr;
      return copy;
   }
   else {
      return getNextGreatest(root->left_);
   }
}


//-------------------------- remove ---------------------------------------
// Removes a given comparable from the tree. If the node holding the
// comparable is removed, proper SearchTree ordering is maintained
// Postconditions: returns false if the tree is empty.
//                 returns true if the comparable was deleted successfully
//                 proper SearchTree order is maintained if a node is deleted
//                 returns false if the comparable is not in the tree
// Function Calls: deleteNode() a recursive helper function to delete and
//                 search for a given comparable
bool SearchTree::remove(const Comparable& toDel)
{
   // tree is empty
   if (root_ == nullptr) {
      return false;
   }

   return deleteNode(root_, toDel);
}


//-------------------------- retrieve --------------------------------------
// Returns a pointer to a given comparable. If the comparable is not found 
// nullptr is returned
// Preconditions:   The comparable must be defined
// Postconditions:  If a comparable is found in a tree a constant pointer
//                  to that comparable is returned. If it is not found
//                  a nullptr is returned
// Function Calls: searchHelper() is called to each the tree and return
//                 a pointer the node holding the comparable
const Comparable* SearchTree::retrieve(const Comparable& toGet) const
{
   STNode* nodeHolding = searchHelper(root_, toGet);
   return nodeHolding == nullptr ? nullptr : nodeHolding->held_;
}


//-------------------------- DepthHelper --------------------------------------
// Recursivley traverses the SearchTree looking for a given comparable. The
// Depth of the comparable is defined as the height from the node holding the
// comparable to the root of the tree.
// Preconditions:   The calling tree exists children are not deleted
// Postconditions:  an integer depth is returned, -1 for not found, 0 if held
//                   in the root, or >1 elsewhere in the tree.
int SearchTree::depthHelper(STNode* root, const Comparable& toFind) const
{
   if (root == nullptr) {
      return -1;
   }

   if (*root->held_ == toFind) {
      return 0;
   }

   int depth;
   // determine which way to traverse the tree
   if (*root->held_ < toFind) {
      depth = depthHelper(root->right_, toFind);
   }
   else {
      depth = depthHelper(root->left_, toFind);
   }

   if (depth == -1) {
      return -1;
   }
   else {
      return 1 + depth;
   }
}


//-------------------------- depth --------------------------------------
// Returns the integer depth of where the comparable is stored. Depth
// is defined as the number of edged from the root of the tree to the
// node holding the comparable
// Postconditions:  If a comparable is found in a tree the depth is
//                  returned. If a comparable is found in the root
//                  0 is returned. If the comparable is not found
//                  -1 is returned
// Function Calls: depthHelper() to recusively travserse and compute
//                 the depth of a given comparable
int SearchTree::depth(const Comparable& toFind) const
{
   int nodeDepth = depthHelper(root_, toFind);
   return nodeDepth;
}


//-------------------------- max --------------------------------------
// Returns the maximum of two given integers
// Postconditions:  The maximum of two integers is returned
int SearchTree::max(int first, int second) const
{
   return first > second ? first : second;
}


//-------------------------- HeightHelper -------------------------------------
// Recursively traverses the tree from a given root to the furthest away leaf 
// node in its lineage. Returns an integer representing that height.
// Preconditions:   The root passed in has the comparable we are looking for 
// Postconditions:  an integer depth is returned, 0 if held a lead node and
//                  a value of >1 elsewhere in the tree.
int SearchTree::heightHelper(STNode* root) const
{
   if (root == nullptr) {
      return 0;
   }
   else if (root->left_ == nullptr && root->right_ == nullptr) {
      return 0;
   }
   else {
      return 1 + max(heightHelper(root->right_),
         heightHelper(root->left_));
   }
}


//-------------------------- SearchHelper -------------------------------------
// Recursively searches the SearchTree looking for a given comparable
// Preconditions :  The root of the calling tree must be passed in
// Postconditions:  Returns a pointer to a node in a given tree. If the
//                  comparable is not found, nullptr is returned. If the tree
//                  has no root node, nullptr is returned
SearchTree::STNode* SearchTree::searchHelper(STNode* root,
   const Comparable& toFind) const
{
   if (root == nullptr) {
      return nullptr;
   }

   // recursively search the tree for a comparable
   if (*root->held_ == toFind) {

      return root;
   }
   else if (*root->held_ > toFind) {
      return searchHelper(root->left_, toFind);
   }
   else {
      return searchHelper(root->right_, toFind);
   }
}


//-------------------------- height --------------------------------------
// Returns the integer height from where the comparable is stored. Height
// is defined as the number of edged from the node storing the comparable
// to the furthest away leaf node in its lineage.
// Postconditions:  If a comparable is found in a tree the height is
//                  returned. If a comparable is found in a leaf
//                  0 is returned. If the comparable is not found
//                  -1 is returned
// Function Calls: searchHelper() to determine if a comparable is in the
//                 tree
//                 heightHelper() to recusively travserse and compute
//                 the height of a given comparable
int SearchTree::height(const Comparable& toFind) const
{
   if (root_ == nullptr) {
      return -1;
   }
   else {
      STNode* getHeightOf = searchHelper(root_, toFind);

      if (getHeightOf == nullptr) {
         return -1;
      }
      else {
         return heightHelper(getHeightOf);
      }
   }
}

bool SearchTree::isEmpty() const
{
    return root_ == nullptr;
}


//-------------------------- StreamInorder ------------------------------------
// Recursively traverses the calling tree in order streaming out the comparable
// and the count of the comparable.
// Preconditions : A valid output refrence is provided
// Postconditions: the calling tree is streamed out in sorted order 
void SearchTree::streamInorder(STNode* root, std::ostream& output) const
{
   if (root == nullptr) {
      return;
   }

   streamInorder(root->left_, output);
   // changed to use print
   root->held_->print();
   output << " " << root->count_ << std::endl;
   streamInorder(root->right_, output);
}


//-------------------------- operator<< ---------------------------------------
// Streams the tree out listing the comarables and their counts in sorted order
// Preconditions : The output must be defined and the tree to be streamed must
//                 be defined
// Postconditions:  outputs the tree listing the comarables and their counts 
//                  in sorted order
std::ostream& operator<<(std::ostream& output, const SearchTree& toStream)
{
   toStream.streamInorder(toStream.root_, output);
   return output;
}