#include "CommandBuy.h"

CommandBuy::CommandBuy(std::string type) :
   Command(type)
{
}

CommandBuy::~CommandBuy()
{
}

int CommandBuy::hash() const
{
    return HashableObject::getID()[0] - 'A';
}

/*
const CommandBuy* CommandBuy::create(std::string type)
{
   
   return nullptr;
}
*/

void CommandBuy::execute(TransactionManager*& tManager, ItemsManager*& iManager, CustomerManager*& cManager, std::string& command) const
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
   command.erase(0, 5);

   const Customer* customer = cManager->findCustomer(custNum);

   if (customer == nullptr) {
      // throw
   }

   const Collectible* item = iManager->manageBuying(command);

   if (item == nullptr) {
      //throw
   }

   tManager->logTransaction(customer, item, HashableObject::getID());


}

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

