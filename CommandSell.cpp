// Blake Berry
// 03/08/2022
// Homework 4
// This file is an implimentation for the CommandSell class. The CommandSell
// class inherits from the command interface. The CommandSell class
// is responsible for the end - to - end execution of sale of an item to the
// collectibles store
//-----------------------------------------------------------------------------


#include "CommandSell.h"


//-------------------------- constructor -----------------------------------
// creates a CommandSell with a given string Indicator
// Postconditions: A CommandSell is created
CommandSell::CommandSell(std::string type) :
   Command(type)
{
}


//-------------------------- destructor -----------------------------------
// Frees any dynamic memory associated with the Command object
// Postconditions: The command is freed of any dynamic memory
CommandSell::~CommandSell()
{
}


//-------------------------- Execute -----------------------------------
// Facilitates the sale of an items from the store. Exceptions are
// thrown at a lower level allowing us to avoid if statements
// Postconditions: The sale of an item to the store is executed
//                 if there is any invalid inputs an exception is thrown
void CommandSell::execute(TransactionManager*& tManager,
                          ItemsManager*& iManager, 
                          CustomerManager*& cManager, 
                          std::string& command) const
{
   std::string custNum = getCustomer(command);

   const Customer* customer = cManager->findCustomer(custNum);

   const Collectible* item = iManager->manageSelling(command);

   tManager->logTransaction(customer, item, HashableObject::getID());
}
