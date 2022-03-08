#include "CommandCustomer.h"


//-------------------------- constructor -----------------------------------
// creates a CommandCustomer with a given string Indicator
// Postconditions: A CommandCustomer is created
CommandCustomer::CommandCustomer(std::string type) :
   Command(type)
{
}

CommandCustomer::~CommandCustomer()
{
}


//-------------------------- Execute -----------------------------------
// Facilitates the display of a customer entire transaction history.
// If there is no such customer or transaction history an exception
// is thrown
// Postconditions: The entire transaction history for a given customer is
//                 displayed in chronolgoical order
// 
//                 If there is no such customer or transaction history an 
//                 exception is thrown
void CommandCustomer::execute(TransactionManager*& tManager, 
                              ItemsManager*& iManager, 
                              CustomerManager*& cManager, 
                              std::string& command) const
{

   std::string custNum = getCustomer(command);

   const Customer* customer = cManager->findCustomer(custNum);

   tManager->displayCustomersHistroy(customer);
}
