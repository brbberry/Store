#include "CommandSell.h"

CommandSell::CommandSell(std::string type) :
   Command(type)
{
}

CommandSell::~CommandSell()
{
}



void CommandSell::execute(TransactionManager*& tManager, ItemsManager*& iManager, CustomerManager*& cManager, std::string& command) const
{
   //first we get the customer

// possibly move this to command becuase will always be this format for getting customer number
// get rid of ", "
   command.erase(0, 2);
   std::string custNum = command.substr(0, 3);
   // check custNum;
   bool allDigits = true;
   int custNumSize = custNum.size();
   for (int i = 0; i < custNumSize; i++) {
      allDigits = std::isdigit(custNum[i]);
   }

   if (!allDigits) {
      // throw an error
   }

   // gets rid of "XXX, "
   command.erase(0, 5);

   const Customer* customer = cManager->findCustomer(custNum);

   if (customer == nullptr) {
      // throw
   }

   const Collectible* item = iManager->manageSelling(command);

   if (item == nullptr) {
      //throw
   }

   tManager->logTransaction(customer, item, HashableObject::getID());


}
