// Blake Berry
// 03/08/2022
// Homework 4
// This file is an interface for the TransactionManager class. The 
//  TransactionManager stores customers and their purchase history for the 
// collectibles store. The transactionManager does not own the memory to the
// customer or the items in the transaction it simply logs and can provide
// hisotrical information about a csutomers or the stores transaction history
//-----------------------------------------------------------------------------

#include "TransactionManager.h"
#include "ItemsManager.h"
#include "CustomerManager.h"
#include <fstream>
#include <iostream>



//-------------------------- TransactionManager ----------------------------
// creates a transaction manager that is empty of transaction to manage
// Postconditions: creates a transaction manager that is empty of 
//                 transactions
TransactionManager::TransactionManager() :
   transactionHistory_(nullptr)
{
   transactionHistory_ = new SearchTree();
}


//------------------------- Destructor ----------------------------
// Frees the transactionHistory tree of its nodes
// Preconditions : Assumes that the collectibles and customers free their
//                 own dynamic memory
// Postconditions: Frees the memory associated with the transactionManager
TransactionManager::~TransactionManager()
{
   delete transactionHistory_;
}


//------------------------- logTransaction ----------------------------
// Given a customer, item, and transaction type a transaction object is 
// created and stored in the transaction history
// Preconditions : Assumes that the collectibles and customers free their
//                 own dynamic memory
// Postconditions: Frees the memory associated with the transactionManager
bool TransactionManager::logTransaction(const Customer*& responsible, 
                                        const Collectible*& item, 
                                        std::string transactionType)
{

   if (responsible == nullptr) {
      // throw an error
      return false;
   }

   // make new transaction with refrence to the true memory
   Transaction* newTransaction = new Transaction(item, transactionType);
   // make a new transaction log 
   TransactionLogEntry* transactionEntry = nullptr;
   transactionEntry = new TransactionLogEntry(responsible, newTransaction);

   const Comparable* toAdd = static_cast<const Comparable*>(transactionEntry);

   // insert returns false if the entry is already present
   // that is an entry with that exact customer is already present still 
   // need to add transaction
   if (!transactionHistory_->insert(toAdd)) {
      // if the entry was already in the table the count was increased but 
      // we need to add the transaction
      const Comparable* entryToAddTo = transactionHistory_->retrieve(*toAdd);
      const TransactionLogEntry* addHere = nullptr;
      addHere = static_cast<const TransactionLogEntry*>(entryToAddTo);

      // add the transaction
      addHere->addTransaction(new Transaction(*newTransaction));

      // clear the already present entry -- deletes origional transaction
      delete transactionEntry;
   }

   return true;
}



//------------------------- DisplayTransactionHistory ----------------------
// Traverses the transaction history tree and prints out all of the 
// customers in alphebtic order and prints their transaction in chrological
// order
// Preconditions : Assumes that the print method exists for TransactionEntry
// Postconditions: prints to the console the transaction history for each 
//                 customer. Each transaction will appear on one line
//                 indented by a tab under the customers name
void TransactionManager::displayTransactionHistory() const
{
   std::string boarder2 = "------------------------";
   std::string boarder = "--------------";
   std::cout << boarder + " Transaction History " + boarder2 << std::endl;
   std::cout << *transactionHistory_ << std::endl;

}


//------------------------- DisplayCustomerHistory -------------------------
// Traverses the tree looking for a given customer. If found the customers
// transaction history is displayed in chronological order
// Preconditions : Assumes that the print method exists for TransactionEntry
// Postconditions: prints to the console the transaction history for the 
//                 customer. Each transaction will appear on one line
//                 indented by a tab under the customers name
//                  
//                 if the customer has not made a transaction an exception
//                 is thrown
void TransactionManager::displayCustomersHistroy(const Customer*& responsible)
const
{
   std::string boarder1 = "------------- ";
   std::string boarder2 = "-----------------------";
   std::cout << boarder1 << responsible->getName() << " Transaction History"
      + boarder2 << std::endl;
   TransactionLogEntry dummyToSearch(responsible);
   const Comparable* toMatch = static_cast<const Comparable*>(&dummyToSearch);
   const Comparable* found = transactionHistory_->retrieve(*toMatch);
   if (found == nullptr) {
      
      std::string name = responsible->getName();
      std::cout << name + " has not made any transactions" << std::endl;
   }
   else {
      std::cout << *found << std::endl;
   }
}