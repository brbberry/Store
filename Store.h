// Blake Berry
// 03/08/2022
// Homework 4
// This file is an interface for the Store class. The Store class is an
// abstract base class that defines basic behavior for a general store.
// The store class mandates a store has specific managers and a command factory
// all of which execute and run off of files.
//------------------------------------------------------------------------------

#pragma once

#include <iostream>
#include <fstream>

class Store
{

protected:


   static const int NUM_COMMANDS = 26; // cannot be fewer than 1

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


   //-------------------- hashCommands ----------------------------
   // Each store must decide how it hashes its own commands
   // PreConditions : the key needs to be a string
   // Postconditions: an integer hash is produced
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

