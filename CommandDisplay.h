// Blake Berry
// 03/08/2022
// Homework 4
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


   //-------------------------- Execute -----------------------------------
   // Facilitates the display of the stores entire inventory.
   // Postconditions: The entire stores inventory is displayed with the
   //                 the coins printed first, the comics second and the
   //                 sports cards last each in sorted order
   virtual void execute(TransactionManager*& tManager,
      ItemsManager*& iManager,
      CustomerManager*& cManager,
      std::string& command) const;
};

