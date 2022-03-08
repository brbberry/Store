// Blake Berry
// 03/08/2022
// Homework 4
// This file is an implimentation for the CommandDisplay class. The 
// CommandDisplay class inherits from the command interface. The CommandDisplay 
// class is responsible for the end - to - end execution of displaying the 
// stores item inventory
//-----------------------------------------------------------------------------


#include "CommandDisplay.h"


//-------------------------- constructor -----------------------------------
// creates a CommandDisplay with a given string Indicator
// Postconditions: A CommandDisplay is created
CommandDisplay::CommandDisplay(std::string type) :
   Command(type)
{
}


//-------------------------- destructor -----------------------------------
// Frees any dynamic memory associated with the Command object
// Postconditions: The command is freed of any dynamic memory
CommandDisplay::~CommandDisplay()
{
}


//-------------------------- Execute -----------------------------------
// Facilitates the display of the stores entire inventory.
// Postconditions: The entire stores inventory is displayed with the
//                 the coins printed first, the comics second and the
//                 sports cards last each in sorted order
void CommandDisplay::execute(TransactionManager*& tManager, 
                             ItemsManager*& iManager, 
                             CustomerManager*& cManager,
                             std::string& command) const
{
   iManager->showInventory();
}
