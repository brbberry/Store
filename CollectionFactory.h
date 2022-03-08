// Blake Berry
// 03/08/2022
// Homework 4
// This file is an interface for the CollectionFactory class. The
//  CollectionFactory class has a hashtable that is capable of generating
// Collectible objects that represent items that can be acted upon sold bought
// at a collectibles store
//-----------------------------------------------------------------------------


#pragma once
#include "Collectible.h"
#include "Coin.h"
#include "SportsCard.h"
#include "Comic.h"
#include <vector>

class CollectionFactory
{
private:

   static const int FACTORY_SIZE = 26; // the number of collectibles possible
                                       // for this factory. Cannot be less than
                                       // 1

   HashableObject** itemsFactory_;     // hashtable filled with collectibles


   //-------------------------- hashCollectible  ------------------------------
   // Takes a collectibles key and hashes it for quick access in the factory
   // Preconditions : The key is the first char of the string and is between
   //                 'A' and 'Z'
   // Postconditions: returns an integer hash of the collectibles key
   int hashCollectible(std::string collectionType) const;


   //-------------------------- validCollectibleHash --------------------------
   // Returns a bool for if the hash is valid given the current collection
   // factory
   // Preconditions : The key has been hashed appropriately
   // Postconditions: returns true if the index is between 0 and FACTORY_SIZE
   //                 false otherwise
   bool validCollectibleHash(int collectionIndex) const;


public:

   //-------------------------- constructor -----------------------------------
   // Fills the collection factory with the basic collectibles that it should 
   // be able to create
   // Preconditions : the FACTORY_SIZE must be greater than 1
   // 
   //                 Assumes no collisions -- meaning each collectible has a
   //                 unique key
   // Postconditions: The factory will be filled with collectibles through
   //                 hashing
   CollectionFactory();


   //-------------------------- destructor -----------------------------------
   // Frees the memory associated with the factory
   // Preconditions : the hashable object frees its own dynamically allocated
   //                 memory
   // Postconditions: The hashtable is cleared of all the dynamic memory that  
   //                 is associated
   ~CollectionFactory();


   //-------------------------- create ----------------------------------------
   // Given a key a collectible pointer is returned containg this value. The
   // value is a shell of a collectible from the factory
   // PreConditions : The first element is the key associated with the
   //                 collectible
   // Postconditions: a constant Hashable object pointer is returned from a key
   const Collectible* create(std::string key) const;
};

