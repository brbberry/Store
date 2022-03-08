// Blake Berry
// 02/22/2022
// Homework 4 design
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
   // PsuedoCode
   /*
   
      adds items line by line for the item manager to process

      if an exception is thrown, the line is skipped the error message is 
      displyed and the next line is processed
   
   */


   //----------------- initalizeTransactionManager ----------------------------
   // Creates the transaction manager 
   // PreConditions : Needs to be initialized before the store is ran
   // Postconditions: The transaction manager is created
   virtual void initalizeTransactionManager();
   // PsuedoCode
   /*

      initalizes to nullptr

   */


   //-------------------- initalizeCustomerManager ----------------------------
   // Creates the customer manager, initalizing the customer list from a file
   // PreConditions : Needs to be initialized before the store is ran
   //                 The file is assumed to be formatted but not necessarily
   //                 valid
   // Postconditions: The customer manager is created along with the stores
   //                 customerlist
   virtual void initalizeCustomerManager(std::ifstream& readCustomers);
   // PsuedoCode
   /*
      // including loops 
      // include while loops
      adds customers line by line for the item manager to process

      if an exception is thrown, the line is skipped the error message is
      displyed and the next line is processed

   */

   virtual int hashCommands(std::string key) const;

public:

   //-------------------------- Constructor ------------------------------------
   // Creates a store with an inventory, customer list, and a way to manage 
   // transactions. 
   // Preconditions : The Manager classes and factory classes must be 
   //                 implimented
   // Postconditions: A store with an inventory, customer list, and empty 
   //                 transaction log is created and can be ran for operation
   CollectibleStore();
   // PsuedoCode
   /*

      calls initalizeCustomerManager and initalizeItemsManager
      calls transactionManager default constructor
      calls CollectiblesFactory default constructor

   */


   //-------------------------- destructor -----------------------------------
   // Frees the memory associated with the store
   // Preconditions : The managers desructors free their associated memory
   // Postconditions: The store is cleared of all the dynamic memory that is 
   //                 associated
   ~CollectibleStore();
   // PsuedoCode
   /*

      frees the data memebers

   */


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
   //Psuedocode
   /*

      while we are not at the end of the file
         read in and store the first line

         process the first letter, creating and storeing a command from the
         comand factory

         try to execute the command with the store managers and the
         command line
         
         catch the exception and process the next line of code 
         outputting the error
            

   */
   void fillStoreInventory(std::ifstream& readInventory);

   void fillStoreCustomers(std::ifstream& readCustomers);


   //------------------------ main ----------------------------------------
   // Operates the store
   // PreConditions : The files are correctly formatted
   // Postconditions: The store is ran and operated with any commands displayed
   //                 to the console.
   /*
   int main() {

      // initialize CollectibleStore store(file1, file2 );
      // store.runStore(CommandFile)

      return 0;
   }
   */
};

