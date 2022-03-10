// Blake Berry
// 03/08/2022
// Homework 4
// This file is an interface for the CollectionFactory class. The
//  CollectionFactory class has a hashtable that is capable of generating
// Collectible objects that represent items that can be acted upon sold bought
// at a collectibles store
//-----------------------------------------------------------------------------

#include "CollectionFactory.h"


//-------------------------- hashCollectible  ------------------------------
// Takes a collectibles key and hashes it for quick access in the factory
// Preconditions : The key is the first char of the string and is between
//                 'A' and 'Z'
// Postconditions: returns an integer hash of the collectibles key
int CollectionFactory::hashCollectible(std::string collectionType) const
{
   return collectionType[0] - 'A';
}


//-------------------------- validCollectibleHash --------------------------
// Returns a bool for if the hash is valid given the current collection
// factory
// Preconditions : The key has been hashed appropriately
// Postconditions: returns true if the index is between 0 and FACTORY_SIZE
//                 false otherwise
bool CollectionFactory::validCollectibleHash(int collectionIndex) const
{
   if (collectionIndex < FACTORY_SIZE && collectionIndex >= 0) {
      return true;
   }
   return false;
}


//-------------------------- constructor -----------------------------------
// Fills the collection factory with the basic collectibles that it should 
// be able to create
// Preconditions : the FACTORY_SIZE must be greater than 1
// Postconditions: The factory will be filled with collectibles through
//                 hashing
CollectionFactory::CollectionFactory() :
   itemsFactory_(nullptr)
{

   itemsFactory_ = new HashableObject * [FACTORY_SIZE];
   for (int i = 0; i < FACTORY_SIZE; i++) {
      itemsFactory_[i] = nullptr;
   }

   // if more collectibles are added they must be instantiated here
   HashableObject* coin = new Coin();
   HashableObject* comic = new Comic();
   HashableObject* sportsCard = new SportsCard();

   // then pushed to the back of this vector for processing
   std::vector<HashableObject*> addToFactory;
   addToFactory.push_back(coin);
   addToFactory.push_back(comic);
   addToFactory.push_back(sportsCard);

   int numToAddToFactory = addToFactory.size();

   for (int i = 0; i < numToAddToFactory; i++) {
      int index = hashCollectible(addToFactory[i]->getID());
      if (validCollectibleHash(index)) {
         itemsFactory_[index] = addToFactory[i];
      }
   }
}


//-------------------------- destructor -----------------------------------
// Frees the memory associated with the factory
// Preconditions : the hashable object frees its own dynamically allocated
//                 memory
// Postconditions: The hashtable is cleared of all the dynamic memory that  
//                 is associated
CollectionFactory::~CollectionFactory()
{
   for (int i = 0; i < FACTORY_SIZE; i++) {
      delete itemsFactory_[i];
      itemsFactory_[i] = nullptr;
   }
   delete[] itemsFactory_;
}


//-------------------------- create ----------------------------------------
// From a given key a value is returned if it exists
// Postconditions: a constant Hashable object pointer is returned from a key
const Collectible* CollectionFactory::create(std::string key) const
{

   int collectibleIndex = hashCollectible(key);
   if (validCollectibleHash(collectibleIndex)) {
      if (itemsFactory_[collectibleIndex] != nullptr) {
         Collectible* found = static_cast<Collectible*>
                              (itemsFactory_[collectibleIndex]);

         return found;
      }
   }
   return nullptr;
}
