// Blake Berry
// 02/22/2022
// Homework 4 Design
// This file is an interface for the CommandSell class. The CommandSell
// class inherits from the command interface. The CommandSell class
// is responsible for the end - to - end execution of sale of an item to the
// collectibles store
//-----------------------------------------------------------------------------

#pragma once
#include "Command.h"

class CommandSell : public Command
{
public:

   //-------------------------- constructor -----------------------------------
   // creates a CommandSell with a given string Indicator
   // Postconditions: A CommandSell is created
   CommandSell(std::string type = "S");


   //-------------------------- destructor -----------------------------------
   // Frees any dynamic memory associated with the Command object
   // Postconditions: The command is freed of any dynamic memory
   ~CommandSell();


   /*
   //-------------------------- Create -----------------------------------
   // Creates a specific CommandBuy based off a string type that is stored
   // in the command class's field (S for commandSell)
   // Postconditions: The commandBuy object is created and returned
   virtual const Command* create(std::string type);
   */

   //-------------------------- Execute -----------------------------------
   // Facilitates the sale of an items from the store. Exceptions are
   // thrown at a lower level allowing us to avoid if statements
   // Postconditions: The sale of an item to the store is executed
   //                 if there is any invalid inputs an exception is thrown
   virtual void execute(TransactionManager*& tManager,
      ItemsManager*& iManager,
      CustomerManager*& cManager,
      std::string& command) const;
   //PSUEDOCODE
   /*

      read until the first comma storing the customer number

      use the customer manager to check if that is a valid customer

      read the string until the next comma storing the collectible type

      check with the item manager that the collection type is valid

      run the dummy collections create method

      use the item manager to check if this item is in the store

      use the item manager to decrease the inventory

      use the transaction manager to log the sale

   */


};

