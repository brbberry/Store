// Blake Berry
// 03/08/2022
// Homework 4
// This file is an interface for the ItemManager class. The ItemManager 
//  class has a collectible Factory and stores a sorted inventory seperated
// by collectible type. The ItemManager class is responsible for making sure
// an item to be acted on is valid or in the store. It is reponsible for
// filling in the stores initial inventory
//-----------------------------------------------------------------------------

#pragma once
#include "Collectible.h"
#include "CollectionFactory.h"
#include "SearchTree.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <ctype.h>
#include "CollectiblesStoreError.h"

class ItemsManager
{

private:

   static const int NUM_ITEM_TYPES = 26; // must be above 1+


   CollectionFactory makeCollectibles_;   // factory that makes collectibles                               

   SearchTree** betterInventory_;         // a hashtable of the inventory Trees


   //------------------------ getItemType ------------------------------------
   // Processes a line of instructions getting the item type from them and
   // returning it
   // Postconditions:  The item type must be 1 char and must be the first char
   //                  in the instructions
   std::string getItemType(std::string& instructions) const;


   //------------------------ getQuantity -------------------------------------
   // Processes a line of input instructions extracting the quantity of a given
   // item
   // Preconditions : The instructions must lead with ", "
   // Postconditions:  returns the quantity if valid and returns -1
   //                  if invalid
   int getQuantity(std::string& instructions) const;


   //------------------------ getItemShell ------------------------------------
   // Takes a given string and checks the item factory for a collectible of 
   // that type. 
   // Postconditions: returns a pointer to a dummy item of the correct type
   //                 otherwise an error is thrown
   const Collectible* getItemShell(std::string& type) const;


   //------------------------ getInventoryAmount ------------------------------
   // Converts the string representation of item quantity to an integer 
   // Postconditions:  returns the quantity integer if a valid quanitity
   //                  string is passed in otherwise an error is thrown
   int getInventoryAmount(std::string& item) const;


   //------------------------ hashStoreInventory ------------------------------
   // Creates an index in the invertory for a given item type
   // Preconditions : Each collectible must have a unique item type
   //                 the first char must between 'A' and 'Z' inclusive
   // Postconditions:  returns a hash for an item type
   int hashStoreInventory(std::string itemType) const;


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
   void fillInventory(std::ifstream& inFile);



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
   const Collectible* manageSelling(std::string collectible);



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
   const Collectible* manageBuying(std::string collectible);

   void showInventory() const;
};

