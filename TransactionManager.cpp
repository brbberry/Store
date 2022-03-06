#include "TransactionManager.h"
#include "ItemsManager.h"
#include "CustomerManager.h"
#include <fstream>
#include <iostream>
TransactionManager::TransactionManager() :
   transactionHistory_(nullptr)
{
   transactionHistory_ = new SearchTree();
}

TransactionManager::~TransactionManager()
{
   delete transactionHistory_;
}

bool TransactionManager::logTransaction(const Customer*& responsible, const Collectible*& item, std::string transactionType)
{

   if (responsible == nullptr) {
      // throw an error
      return false;
   }
   Transaction newTransaction(item, transactionType);

   TransactionLogEntry* transactionEntry = new TransactionLogEntry(responsible, newTransaction);
   const Comparable* toAdd = static_cast<const Comparable*>(transactionEntry);

   // insert returns false if the entry is already present
   if (!transactionHistory_->insert(toAdd)) {
      // if the entry was already in the table the count was increased but we need to add the transaction
      const Comparable* entryToAddTo = transactionHistory_->retrieve(*toAdd);
      const TransactionLogEntry* addHere = static_cast<const TransactionLogEntry*>(entryToAddTo);
      // possibly change to make a copy rather than in the method
      addHere->addTransaction(newTransaction);

      // becauase it was already presesnt delete the log entry
      delete transactionEntry;
   }

   return false;
}


void TransactionManager::displayTransactionHistory() const
{

   std::cout << *transactionHistory_ << std::endl;

}

void TransactionManager::displayCustomersHistroy(const Customer*& responsible) const
{
   TransactionLogEntry dummyToSearch(responsible);
   const Comparable* toMatch = static_cast<const Comparable*>(&dummyToSearch);
   const Comparable* found = transactionHistory_->retrieve(*toMatch);
   if (found == nullptr) {
      // throw error
      std::cout << "error" << std::endl;
   }
   else {
      std::cout << *found << std::endl;
   }

}

int main() {

   ItemsManager* mgrI = new ItemsManager();
   CustomerManager* mgrC = new CustomerManager();
   TransactionManager* mgrT = new TransactionManager();
   std::ifstream inv("C:/Users/Trident/source/repos/StoreTesting/StoreTesting/Text1.txt");
   std::ifstream cus("C:/Users/Trident/source/repos/StoreTesting/StoreTesting/Text.txt");
   mgrI->fillInventory(inv);
   mgrC->fillCustomerLog(cus);

   // not new'd
   const Customer* toUse = mgrC->findCustomer("999");
   //const Collectible* item = mgrI->manageBuying("C, 1938, Mint, Superman, DC");

   delete mgrI, mgrC, mgrT;

   return 0;
}
