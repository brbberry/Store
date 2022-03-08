// Blake Berry
// 03/08/2022
// Homework 4
// This file is an implimentation for the CommandCustomerclass. The 
// CommandCustomer class inherits from the command interface. The 
// CommandCustomer class is responsible for the end - to - end execution of 
// displaying a customers transaction history with the store
//-----------------------------------------------------------------------------

#include "CommandBuy.h"


//-------------------------- constructor -----------------------------------
// creates a CommandBuy with a given Type indicator
// Postconditions: A commandBuy object is created
CommandBuy::CommandBuy(std::string type) :
   Command(type)
{
}


//-------------------------- destructor -----------------------------------
// Frees any dynamic memory associated with the Command object
// Postconditions: The command is freed of any dynamic memory
CommandBuy::~CommandBuy()
{
}


//-------------------------- Execute -----------------------------------
// Facilitates the purchase of an items to the store. Exceptions are
// thrown at a lower level allowing us to avoid if statements
// Postconditions: The purchase of an item to the store is executed
//                 if there is any invalid inputs an exception is thrown
void CommandBuy::execute(TransactionManager*& tManager, 
                         ItemsManager*& iManager, 
                         CustomerManager*& cManager, 
                         std::string& command) const
{

   std::string custNum = getCustomer(command);

   const Customer* customer = cManager->findCustomer(custNum);

   const Collectible* item = iManager->manageBuying(command);

   tManager->logTransaction(customer, item, HashableObject::getID());
}

