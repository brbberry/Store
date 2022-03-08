// Blake Berry
// 02/22/2022
// Homework 4 Design
// This file is an interface for the CommandBuy class. The CommandBuy class
// class inherits from the command interface. The command buy class is 
// responsible for the end - to - end execution of a purchase from a 
// collectible store
//-----------------------------------------------------------------------------

#pragma once
#include "Command.h"
#include <string>
#include <ctype.h>
#include "CollectiblesStoreError.h"

class CommandBuy : public Command
{

public:

   //-------------------------- constructor -----------------------------------
   // creates a CommandBuy with a given Type indicator
   // Postconditions: A commandBuy object is created
   CommandBuy(std::string type = "B");
   

   //-------------------------- destructor -----------------------------------
   // Frees any dynamic memory associated with the Command object
   // Postconditions: The command is freed of any dynamic memory
   ~CommandBuy();


   //-------------------------- Execute -----------------------------------
   // Facilitates the purchase of an items to the store. Exceptions are
   // thrown at a lower level allowing us to avoid if statements
   // Postconditions: The purchase of an item to the store is executed
   //                 if there is any invalid inputs an exception is thrown
   virtual void execute(TransactionManager*& tManager,
      ItemsManager*& iManager,
      CustomerManager*& cManager,
      std::string& command) const;
};

