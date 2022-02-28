// Blake Berry
// 02/22/2022
// Homework 4 Design
// This file is an interface for the CommandDisplay class. The CommandDisplay
// class inherits from the command interface. The CommandDisplay class
// is responsible for the end - to - end execution of displaying the stores
// item inventory
//-----------------------------------------------------------------------------

#pragma once
#include "Command.h"
class CommandDisplay : public Command
{
public:

   //-------------------------- constructor -----------------------------------
// creates a CommandDisplay with a given string Indicator
// Postconditions: A CommandDisplay is created
   CommandDisplay(std::string type = "D");


   //-------------------------- destructor -----------------------------------
   // Frees any dynamic memory associated with the Command object
   // Postconditions: The command is freed of any dynamic memory
   ~CommandDisplay();

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

   //-------------------------- Create -----------------------------------
   // Creates a specific CommandBuy based off a string type that is stored
   // in the command class's field (D for commandDisplay)
   // Postconditions: The commandBuy object is created and returned
   virtual const Command* create(std::string type = "D");


   //-------------------------- Execute -----------------------------------
   // Facilitates the display of the stores entire inventory.
   // Postconditions: The entire stores inventory is displayed with the
   //                 the coins printed first, the comics second and the
   //                 sports cards last each in sorted order
   virtual void execute(TransactionManager& tManager,
      ItemsManager& iManager,
      CustomerManager& cManager,
      std::string command) const;
   //PSUEDOCODE
   /*
         
         use the itemManager to print the inventory
   */
};

