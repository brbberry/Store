#include "TransactionManager.h"

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


//PSUEDOCODE
/*
   store the pointer from a Call the search trees retrieve method
   if the pointer is nullptr
      create a new transaction
      create a new TransactionLogEntry
      insert that into the tree using the BST insert method
   else
      create a new transaction
      cast the comparable pointer to a TransactionLogEntry
      call the transitionLogEntries add transaction method to log it
*/

void TransactionManager::displayTransactionHistory() const
{
}

void TransactionManager::displayCustomersHistroy(const Customer& reponsible) const
{
}

