// Blake Berry
// 02/22/2022
// Homework 4 design
// This file is an interface for the Store class. The Store class is an
// abstract base class that defines basic behavior for a general store.
// The store class mandates a store has specific managers and a command factory
// all of which execute and run off of files.
//------------------------------------------------------------------------------

#pragma once
#include "ItemsManager.h"
#include "TransactionManager.h"
#include "CustomerManager.h"
#include "Command.h"
#include <iostream>
#include <fstream>

class Store
{

protected:

   ItemsManager*        iManager_; // manages the stores invetory
                                  // and the items associated

   TransactionManager*  tManager_; // manages the transactions
                                  // and the transaction history

   CustomerManager*     cManager_; // manages the list of customers

   // the commands will take in all three managers as we dont know
   // which command is needed to execute
   Command** generateCommand_; // processes store commands

   static const int NUM_COMMANDS = 26;

   //------------------------ initalizeItemsManager ---------------------------
   // Creates the stores inventory from a file of items.
   // PreConditions : Needs to be initialized before the store is ran
   //                 The infile must be formatted correctly but not 
   //                 necessarily valid
   // Postconditions: The Item store manager is created along with the stores
   //                 inventory
   virtual void initalizeItemsManager(std::ifstream& readInventory) = 0;


   //----------------- initalizeTransactionManager ----------------------------
   // Creates the transaction manager 
   // PreConditions : Needs to be initialized before the store is ran
   // Postconditions: The transaction manager is created
   virtual void initalizeTransactionManager() = 0;


   //-------------------- initalizeCustomerManager ----------------------------
   // Creates the customer manager, initalizing the customer list from a file
   // PreConditions : Needs to be initialized before the store is ran
   //                 The file is assumed to be formatted but not necessarily
   //                 valid
   // Postconditions: The customer manager is created along with the stores
   //                 customerlist
   virtual void initalizeCustomerManager(std::ifstream& readCustomers) = 0;

   virtual int hashCommands(std::string key) const = 0;

public:

   //-------------------------- destructor -----------------------------------
   // Frees the memory associated with the store
   // Postconditions: The store is cleared of all the dynamic memory that is 
   //                 associated
   virtual ~Store() {};


   //------------------------ runStore ----------------------------------------
   // Operates the store, processes store commands from a file, and displays to
   // the console.
   // PreConditions : The store managers must be initialized
   //                 The infile must be formatted correctly but not 
   //                 necessarily valid
   // Postconditions: The store managers are modified by the commands file
   //                 and the store operations that can display to the console
   //                 display to the console.
   virtual void runStore(std::ifstream& readCommands) = 0;
};

