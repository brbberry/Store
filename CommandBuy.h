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

   //-------------------------------- Hash -----------------------------------
   // generates an int from the value that the Command holds
   // Preconditions : Assumes that the key is a capital ASCII value A-Z
   // Postconditions: an integer is returned based off the value held by the 
   //                 command object
   int hash() const;
   //PSUEDOCODE
   /*
      returns ASCII value for command - ASCII A
   
   */

   /*
   //-------------------------- Create -----------------------------------
   // Creates a specific CommandBuy based off a string type that is stored
   // in the command class's field (B for commandBuy)
   // Postconditions: The commandBuy object is created and returned
   virtual const CommandBuy* create(std::string type = "B");
   */

   //-------------------------- Execute -----------------------------------
   // Facilitates the purchase of an items to the store. Exceptions are
   // thrown at a lower level allowing us to avoid if statements
   // Postconditions: The purchase of an item to the store is executed
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

      use the item manager to increase the inventory

      use the transaction manager to log the purchase
   
   */
};

