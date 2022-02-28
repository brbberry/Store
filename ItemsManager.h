// Blake Berry
// 02/22/2022
// Homework 4 design
// This file is an interface for the ItemManager class. The ItemManager 
//  class has a collectible Factory and stores a sorted inventory seperated
// by collectible type. The ItemManager class is responsible for making sure
// an item to be acted on is valid or in the store. It is reponsible for
// filling in the stores initial inventory
//-----------------------------------------------------------------------------

#pragma once
#include "HashTable.h"
#include "Collectible.h"
#include "CollectionFactory.h"
#include "SearchTree.h"

class ItemsManager
{

private:

   CollectionFactory makeCollectibles_;   // factory that makes collectibles 
   std::vector<SearchTree> inventory_;    // stores one type of collectible
                                          // at each index in sorted order


   //-------------------------- CheckStore ------------------------------------
   // Checks if a given collectible is in the inventory
   // Postconditions:  If a collectible is found in the store true is returned
   //                  If it is not found an error is thrown
   // Function Calls:  retrieve is called to check the search tree for a given
   //                  comparable
   bool CheckStore(const Comparable& toGet) const;
   //PSUEDOCODE
   /*
      cast comparable to a collectible
      get and store Collectible Type
      if its a coin
         call retrieve on the first slot in the inventory
         if nullptr is returned
            throw error
         else
            return true
   */


   //-------------------------- makeDummyCollectible --------------------------
   // Creates a dummy collectible based off of a string ID
   // Preconditions :  The factory has to exist
   // Postconditions:  returns a constant pointer that holds the appropriate
   //                  collectible type if it exists
   //                  otherwise an exception is thrown
   const Collectible* makeDummyCollectible(std::string ID) const;


public:

   //-------------------------- Default Constructor ---------------------------
   // Creates an Item manager with a fully working factory and an empty 
   // inventory
   // Preconditions : The factory must be intialized with the items that are
   //                 allowed in the collections store
   // Postconditions: a new item manager is created
   ItemsManager();


   //-------------------------- Destructor -----------------------------------
   // Frees any dynamic memory associated with the items manager class
   // Preconditions : The factory must be capable to freeing its dynamic memory
   //                   
   //                 the items inventory must be capable of freeing its 
   //                 dynamic memory
   // 
   // Postconditions: frees the memory associated with the items manager
   ~ItemsManager();

   
   //-------------------------- FillInventory ---------------------------------
   // Fills the inventory from a file, Coins are index 0, Comics are index 2, 
   // and SportsCards are index 3
   // Preconditions : The factory must be initialized
   // 
   //                 The file must be formatted correctly
   // 
   // Postconditions: The ItemManagers inventory is filled, exceptions are 
   //                 thrown if invalid data is attempted
   void fillInventory(/* file */);
   // PSUEDOCODE
   /*
      while we are not at the end of the file do
         store first char as a string

         use that string to get a dummy collectible from the factory
         if nullptr is returned
            throw an invalid error and keep processing
         else
            try
               call the collectibles create method on the remainder of
               the string

            catch
               the exception and go to the next line of the file

           if the collectible is in the store
               increase the count
           else
               add call insert to add it to the inventory

   */


   //-------------------------- ManageSelling ---------------------------------
   // Given the ID of an item them method handles the sale of an item
   // if the item is present its inventory count is incrimented appropriately
   // Preconditions : the hashable object frees its own dynamically allocated
   //                 memory
   // 
   //                 The factory must be initalized
   // 
   // Postconditions: An item is sold and the inventory is updated and true
   //                 is returned. Throws an error if an invalid item is
   //                 attempted to be sold
   bool manageSelling(std::string ID);
   // PSUEDOCODE
   /*
      generate and store with the item factor a comparable with they give ID
      int index;
      if its a coin
         set index to 0
      if its a Comic
         set index to 1
      if its a SportsCard
         set index to 2

      search the stores inventory at index

      if the item is found 
         increase the count
      if the item is not 
         throw not able to sell to store exception

   */


   //-------------------------- ManageBuying ---------------------------------
   // Given the ID of an item them method handles the purchase of an item
   // if the item is present its inventory count is decrimented appropriately
   // Preconditions : the hashable object frees its own dynamically allocated
   //                 memory
   // 
   //                 The factory must be initalized
   // 
   // Postconditions: An item is sold and the inventory is updated and true
   //                 is returned. Throws an error if an invalid item is
   //                 attempted to be purchased
   bool manageBuying(std::string ID);
   // PSUEDOCODE
   /*
      generate and store with the item factor a comparable with they give ID
      int index;
      if its a coin
         set index to 0
      if its a Comic
         set index to 1
      if its a SportsCard
         set index to 2

      search the stores inventory at index

      if the item is found && the count is not 0
         decrease the count
      if the item is not
         throw not able to buy exception

   */


};

