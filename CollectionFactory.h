// Blake Berry
// 02/22/2022
// Homework 4 design
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

class CollectionFactory
{
private:

   static const int FACTORY_SIZE = 26; // the number of collectibles possible
                                       // for this factory

   HashableObject** itemsFactory_;             // hashtable filled with collectibles
   int size_;


   int hashCollectible(std::string collectionType) const;

   bool validCollectibleHash(int collectionIndex) const;


public:

   //-------------------------- constructor -----------------------------------
   // Fills the collection factory with the basic collectibles that it should 
   // be able to create
   // Preconditions : the collectible objects will need to be hashable
   // Postconditions: The hashtable will be filled with the dummy nodes
   CollectionFactory(int size = FACTORY_SIZE);
   // PSUEDOCDOE
   /*
      instantiate itemsFactory to size of FACTORY_SIZE

      Make collectible pointers using M for coin
      Make collectible pointers using S for sports card
      Make collectible pointers using C for comicbook

      call insert from factory on each of the collectibles

   */


   //-------------------------- destructor -----------------------------------
   // Frees the memory associated with hashtable
   // Preconditions : the hashable object frees its own dynamically allocated
   //                 memory
   // Postconditions: The hashtable is cleared of all the dynamic memory that  
   //                 is associated
   ~CollectionFactory();


   //-------------------------- create ----------------------------------------
   // From a given key a value is returned if it exists
   // Postconditions: a constant Hashable object pointer is returned from a key
   const Collectible* create(std::string key);
   // PSUEDOCODE
   /*
      creates a collectible from the given ID

      calls hash gets index

      if the hash table has the value
         return the value
      else
         return nullptr
   */



};

