// Blake Berry
// 03/08/2022
// Homework 4
// This file is an implimentation for the CommandHistory class. The 
// CommandHistory class inherits from the command interface. The CommandHistory
// class is responsible for the end - to - end execution of displaying the 
// stores entire customer transaction history
//-----------------------------------------------------------------------------

#include "CommandHistory.h"

//-------------------------- constructor -----------------------------------
// creates a CommandHistroy with a given string Indicator
// Postconditions: A CommandHistory is created
CommandHistory::CommandHistory(std::string type) :
   Command(type)
{
}


//-------------------------- destructor -----------------------------------
// Frees any dynamic memory associated with the Command object
// Postconditions: The command is freed of any dynamic memory
CommandHistory::~CommandHistory()
{
}


//-------------------------- Execute -----------------------------------
// Facilitates the display of the entire store transaction history.
// If there is no such customers or transaction history an exception
// is thrown
// Postconditions: The entire transaction history for a given customer is
//                 displayed in chronolgoical order.
// 
//                 If there is no such customers or transaction history an 
//                 exception is thrown
void CommandHistory::execute(TransactionManager*& tManager, 
                             ItemsManager*& iManager, 
                             CustomerManager*& cManager,
                             std::string& command) const
{
   tManager->displayTransactionHistory();
}
