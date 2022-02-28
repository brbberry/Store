// Blake Berry
// 02/22/2022
// Homework 4 design
// This file is an interface for the StoreCommandFactory class. The
// StoreCommandFactory class has a hashtable that is capable of generating
// command objects that represent actions that can be done at a 
// CollectiblesStore
//------------------------------------------------------------------------------

#pragma once

#include "HashTable.h"
#include "Command.h"
class StoreCommandFactroy : public HashTable
{

   static const int FACTORY_SIZE = 26; // the number of collectibles possible
                                       // for this factory

   HashTable CommandFactory;           // hashtable filled with commands


public:

   //-------------------------- constructor -----------------------------------
   // Fills the collection factory with the basic collectibles that it should 
   // be able to create
   // Preconditions : the collectible objects will need to be hashable
   // Postconditions: The hashtable will be filled with the dummy nodes
   StoreCommandFactroy();
   // PSUEDOCDOE
   /*
      instantiate itemsFactory to size of FACTORY_SIZE

      Make a command pointer using S for CommandSell
      Make a command pointer using B for CommandBuy
      Make a command pointer using C for CommandCustomer
      Make a command pointer using D for CommandSDisplay
      Make a command pointer using H for CommandHistory

      call insert from factory on each of the commands

   */


   //-------------------------- destructor -----------------------------------
   // Frees the memory associated with hashtable
   // Preconditions : the hashable object frees its own dynamically allocated
   //                 memory
   // Postconditions: The hashtable is cleared of all the dynamic memory that  
   //                 is associated
   ~StoreCommandFactroy();


   //-------------------------- create ----------------------------------------
   // From a given key a dummy command is returned if it exists
   // Postconditions: a constant Hashable object pointer is returned from a key
   //                 if it exsits otherwise nullptr is returned
   const Command* create(const std::string& ID);
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

