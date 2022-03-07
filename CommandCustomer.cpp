#include "CommandCustomer.h"

CommandCustomer::CommandCustomer(std::string type) :
   Command(type)
{
}

CommandCustomer::~CommandCustomer()
{
}

int CommandCustomer::hash() const
{
    return 0;
}

void CommandCustomer::execute(TransactionManager*& tManager, ItemsManager*& iManager, CustomerManager*& cManager, std::string& command) const
{
   //first we get the customer

// possibly move this to command becuase will always be this format for getting customer number
// get rid of ", "
   command.erase(0, 2);
   std::string custNum = command.substr(0, 3);
   // check custNum;
   bool allDigits = true;
   for (int i = 0; i < custNum.size(); i++) {
      allDigits = std::isdigit(custNum[i]);
   }

   if (!allDigits) {
      // throw an error
   }

   // gets rid of "XXX, "
   command.erase(0, 4);

   const Customer* customer = cManager->findCustomer(custNum);

   if (customer == nullptr) {
      //throw
   }

   tManager->displayCustomersHistroy(customer);
}
