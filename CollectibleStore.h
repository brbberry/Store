// Blake Berry
// 03/08/2022
// Homework 4
// This file is an interface for the Collectible store class. The
// CollectibleStore class inherets from the store abstract base class.
// The CollectibleStore class is constructed from two files containing a 
// list of customers and a list of collectible items that the store has along
// with their inventory. The CollectibleStore class will run the store given
// a commands file
//------------------------------------------------------------------------------

#pragma once
#include "Store.h"
#include "CommandBuy.h"
#include "CommandHistory.h"
#include "CommandSell.h"
#include "CommandDisplay.h"
#include "CommandCustomer.h"
#include "CollectiblesStoreError.h"
#include <vector>
#include <string>

class CollectibleStore : public Store
{
private:

   //------------------------ getCommandType ---------------------------------
   // takes a string and abstracts the command type 
   // PreConditions : The command type must be one char, the first char in the
   //                 string. Assumed to be 'A' - 'Z'
   // Postconditions: returns a string for the command type and modifies the 
   //                 instructions string removing this char
   std::string getCommandType(std::string& instructions) const;


protected:


   //------------------------ initalizeItemsManager ---------------------------
   // Creates the stores inventory from a file of items.
   // PreConditions : Needs to be initialized before the store is ran
   //                 The infile must be formatted correctly but not 
   //                 necessarily valid
   // Postconditions: The Item store manager is created along with the stores
   //                 inventory
   virtual void initalizeItemsManager(std::ifstream& readInventory);



   //----------------- initalizeTransactionManager ----------------------------
   // Creates the transaction manager 
   // PreConditions : Needs to be initialized before the store is ran
   // Postconditions: The transaction manager is created
   virtual void initalizeTransactionManager();


   //-------------------- initalizeCustomerManager ----------------------------
   // Creates the customer manager, initalizing the customer list from a file
   // PreConditions : Needs to be initialized before the store is ran
   //                 The file is assumed to be formatted but not necessarily
   //                 valid
   // Postconditions: The customer manager is created along with the stores
   //                 customerlist
   virtual void initalizeCustomerManager(std::ifstream& readCustomers);


   //------------------------ hashCommands ---------------------------------
   // takes a string command and generates a hash based off that command
   // PreConditions : The command type must be one char, the first char in the
   //                 string. Assumed valid if 'A' - 'Z'
   // Postconditions: returns an integer hash 'Char' - 'A' for the given
   //                 command
   virtual int hashCommands(std::string key) const;

public:


   //-------------------------- Constructor -----------------------------------
   // Creates a store with an empty managers. The command factory is filled 
   // manually based upon the hash of that command. 
   // Preconditions : The Manager classes and factory classes must be 
   //                 implimented
   // 
   //                 There are at most 26 commands with no commands sharing
   //                 the same key
   // 
   //                 Assumes no collisions
   // Postconditions: A store with an inventory, customer list, and empty 
   //                 transaction log is created
   CollectibleStore();


   //-------------------------- destructor -----------------------------------
   // Frees the memory associated with the store
   // Preconditions : The managers desructors free their associated memory
   // Postconditions: The store is cleared of all the dynamic memory that is 
   //                 associated
   ~CollectibleStore();


   //------------------------ runStore ----------------------------------------
   // Operates the store, processes store commands from a file, and displays to
   // the console.
   // PreConditions : The store managers must be initialized
   //                 The infile must be formatted correctly but not 
   //                 necessarily valid
   // Postconditions: The store managers are modified by the commands file
   //                 and the store operations that can display to the console
   //                 display to the console.
   void runStore(std::ifstream& readCommands);


   //------------------------ fillStoreInventory ---------------------------
   // Fills the store with items and outputs any errors to the console
   // PreConditions : The input file must be formatted correctly even if the
   //                 data is invalid
   // Postconditions: The store is filled with items and any errors are 
   //                 output to the console
   void fillStoreInventory(std::ifstream& readInventory);


   //-------------------- fillStoreCustomers ---------------------------------
   // Fills the store with known customers and outputs any errors to the 
   // console
   // PreConditions : The input file must be formatted correctly even if the
   //                 data is invalid
   // Postconditions: The store is filled with a customer list and any errors
   //  are output to the console
   void fillStoreCustomers(std::ifstream& readCustomers);
};

