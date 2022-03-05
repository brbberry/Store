// Blake Berry
// 01/10/2022
// Homework 1
// This file is an interface for the SearchTree class. The search tree 
// contains node structures that hold a pointer to a comparable object and 
// pointers to left and right children.
//------------------------------------------------------------------------------
#pragma once
#include <iostream>
#include "Collectible.h"

class SearchTree
{

private:

   // inner node struct
   struct STNode {

      const Comparable* held_;       // pointer to a comparable
      STNode* left_;       // pointer to the left child
      STNode* right_;      // pointer to the right child
      int     count_;      // the number of occurances of the comparable
   };

   STNode* root_; // pointer to the root of the tree

   //-------------------------- DepthHelper --------------------------------------
   // Recursivley traverses the SearchTree looking for a given comparable. The
   // Depth of the comparable is defined as the height from the node holding the
   // comparable to the root of the tree.
   // Preconditions:   The calling tree exists children are not deleted
   // Postconditions:  an integer depth is returned, -1 for not found, 0 if held
   //                   in the root, or >1 elsewhere in the tree.
   int depthHelper(STNode* root, const Comparable& toFind) const;

   //-------------------------- HeightHelper -------------------------------------
   // Recursively traverses the tree from a given root to the furthest away leaf 
   // node in its lineage. Returns an integer representing that height.
   // Preconditions:   The root passed in has the comparable we are looking for 
   // Postconditions:  an integer depth is returned, 0 if held a lead node and
   //                  a value of >1 elsewhere in the tree.
   int heightHelper(STNode* root) const;

   //-------------------------- copy ----------------------------------------
   // Recursively creates a deep copy of a tree from the root node passed in
   // A pointer to the deep copied root node for the tree copied is returned
   // Preconditions:   The root of the tree passed in must be defined
   // Postconditions:  A pointer to the deep copied root node for the tree 
   //                  copied is returned
   STNode* copy(STNode* root) const;

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
   STNode* insertHelper(STNode* root, const Comparable& toFind) const;


   //-------------------------- SearchHelper -------------------------------------
   // Recursively searches the SearchTree looking for a given comparable
   // Preconditions :  The root of the calling tree must be passed in
   // Postconditions:  Returns a pointer to a node in a given tree. If the
   //                  comparable is not found, nullptr is returned. If the tree
   //                  has no root node, nullptr is returned
   STNode* searchHelper(STNode* root, const Comparable& toFind) const;


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
   bool deleteNode(STNode*& root, const Comparable& toDel);


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
   void deleteRoot(STNode*& root);


   //----------------------- getAndDeleteNextGreatest ----------------------------
   // Given a node, a pointer to a node holding the next greatest comparable is
   // returned. The found node is free'd from memory
   // Preconditions:   The right child of the root to be deleted must be passed in
   // Postconditions:  The node with the next greatest comparable is found copied 
   //                  and returned. The node found with the next greatest 
   //                  comparable is deleted from the tree.
   STNode* getNextGreatest(STNode*& root);


   //-------------------------- max --------------------------------------
   // Returns the maximum of two given integers
   // Postconditions:  The maximum of two integers is returned
   int max(int first, int second) const;


   //-------------------------- EmptyTreeHelper ----------------------------------
   // Recursively traverses a search tree post order freeing the memeory 
   // associated with a given nodes right and left subtrees and resets the root 
   // node
   // Preconditions : The root of the calling tree must be passed in if the tree
   //                 is to be emptied
   // Postconditions: the left and right subtrees of the root will be freed of 
   //                 memory and the root node of the calling tree will be reset
   void emptyTreeHelper(STNode*& root);


   //-------------------------- StreamInorder ------------------------------------
   // Recursively traverses the calling tree in order streaming out the comparable
   // and the count of the comparable.
   // Preconditions : A valid output is provided
   // Postconditions: the calling tree is streamed out in sorted order 
   void streamInorder(STNode* root, std::ostream& output) const;


   //-------------------------- TwoTreeTraverse ----------------------------------
   // Recursively traverses two trees in preorder checking to see if each tree
   // holds the same comparable with the same count at each node
   // Preconditions : The root of both trees must be input to ensure each tree
   //                 is checked 1:1
   // Postconditions: True is returned if the trees are equal and false is
   //                 returned otherwise
   bool twoTreeTraverse(STNode* firstRoot, STNode* secondRoot) const;

public:


   //-------------------------- Default Constructor ------------------------------
   // Creates a default search tree
   // Postconditions: a search tree with a null root pointer is created
   SearchTree();


   //-------------------------- Copy Constructor ---------------------------------
   // creates a new tree that is a deep copy of a given tree
   // Preconditions : The tree to be copied must be defined
   // Postconditions: creates a new tree that is a deep copy of the one passed in
   // Function Calls: copy, the recursive helper function that creates the deep 
   //                 copy
   SearchTree(const SearchTree& toCopy);


   //-------------------------- Destructor ---------------------------------------
   // Frees the memeory associated with a given tree
   // Postconditions: The memory associated with the calling tree is completely
   //                 free'd. The "tree" after the destrucotr is called is not
   //                 usable
   // Function Calls: makeEmpty() to free all the memory associated with the tree
   //                 except the root
   ~SearchTree();


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
   const SearchTree& operator=(const SearchTree& right);


   //-------------------------- operator!= ---------------------------------------
   // Checks if two trees are not equivilent. Equivilance is defined as each tree 
   // storing the same comparable in the same location and with the same count
   // as the other.
   // Postconditions: Returns true if both trees are not equivilent
   //                 Returns false if the trees are equivilent.
   // Function Calls: operator== is used to determine if they are equal
   bool operator!=(const SearchTree& right) const;


   //-------------------------- operator== ---------------------------------------
   // Checks if two trees are equivilent. Equivilance is defined as each tree 
   // storing the same comparable in the same location and with the same count
   // as the other.
   // Postconditions: Returns true if both trees are equivilent
   //                 Returns false if the trees are not equivilent.
   // Function Calls: twoTreeTraverse is used traverse both trees to check for
   //                 equivilance
   bool operator==(const SearchTree& right) const;


   //-------------------------- Insert ------------------------------------------
   // Inserts a comparable into the search tree, if it is not already present.
   // If the comprable is present its count is increased.
   // Postconditions: If the comparable can be inserted into the tree it is
   //                 inserted maintaing SearchTree properties and true is
   //                 returned. If it is already in the tree, the count of that
   //                 comparable is increased. False is returned
   // Function Calls: InsertHelper() is called to return a pointer to the proper
   //                 insert location
   bool insert(Comparable* toInsert);


   //-------------------------- remove ---------------------------------------
   // Removes a given comparable from the tree. If the node holding the
   // comparable is removed, proper SearchTree ordering is maintained
   // Postconditions: returns false if the tree is empty.
   //                 returns true if the comparable was deleted successfully
   //                 proper SearchTree order is maintained if a node is deleted
   //                 returns false if the comparable is not in the tree
   // Function Calls: deleteNode() a recursive helper function to delete and
   //                 search for a given comparable
   bool remove(const Comparable& toDel);


   //-------------------------- makeEmpty ---------------------------------------
   // Removes all the nodes in a given tree, reseting the tree to its intial
   // state after default construction
   // Postconditions: free's the memeory associated the the trees nodes. The
   //                 root node is set to nullptr
   // Function Calls: emptyTreeHelper() to recursively free the memory
   void makeEmpty();


   //-------------------------- retrieve --------------------------------------
   // Returns a pointer to a given comparable. If the comparable is not found 
   // nullptr is returned
   // Preconditions:   The comparable must be defined
   // Postconditions:  If a comparable is found in a tree a constant pointer
   //                  to that comparable is returned. If it is not found
   //                  a nullptr is returned
   // Function Calls: searchHelper() is called to each the tree and return
   //                 a pointer the node holding the comparable
   const Comparable* retrieve(const Comparable& toGet) const;


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
   int depth(const Comparable& toFind) const;


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
   int height(const Comparable& toFind) const;


   //-------------------------- operator<< ---------------------------------------
   // Streams the tree out listing the comarables and their counts in sorted order
   // Preconditions : The output must be defined and the tree to be streamed must
   //                 be defined
   // Postconditions: outputs the tree listing the comarables and their counts 
   //                 in sorted order
   friend std::ostream& operator<<(std::ostream& output, const SearchTree& toStream);
};
