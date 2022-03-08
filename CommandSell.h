// Blake Berry
// 03/08/2022
// Homework 4
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


   //-------------------------- Execute -----------------------------------
   // Facilitates the sale of an items from the store. Exceptions are
   // thrown at a lower level allowing us to avoid if statements
   // Postconditions: The sale of an item to the store is executed
   //                 if there is any invalid inputs an exception is thrown
   virtual void execute(TransactionManager*& tManager,
      ItemsManager*& iManager,
      CustomerManager*& cManager,
      std::string& command) const;
};

