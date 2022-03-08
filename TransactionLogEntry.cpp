// Blake Berry
// 03/08/2022
// Homework 4
// This file is an implimentation for the TransactionLogEntry class. The 
// TransactionLogEntry class is a sortable class that sorts based upon the
// customer name. The TransactionLogEntry class couples a customer with a list
// of transactions made by that customer. These transactions are stored in 
// chronlogical order
//-----------------------------------------------------------------------------

#include "TransactionLogEntry.h"


//-------------------------- Default Constructor ---------------------------
// Creates an empty entry filled with a null customer and empty transition
// log
// Postconditions: Creates an empty entry filled with a null customer and empty 
// transition log
TransactionLogEntry::TransactionLogEntry() :
   customer_(nullptr),
   transactionLog_(std::vector<Transaction>())
{
}


//-------------------------- Constructor -----------------------------------
// Creates a log entry given a customer and an initial transaction
// Postconditions: Creates an entry for a given customer and logs the
//                 transaction
TransactionLogEntry::TransactionLogEntry(const Customer*& cust, Transaction& initialTransaction) :
   customer_(cust),
   transactionLog_(std::vector<Transaction>())
{
   transactionLog_.push_back(initialTransaction);
}



//-------------------------- Constructor -----------------------------------
// Creates a dummy transitionLogEntry for a given customer
// Postconditions: Creates an entry for a given customer
TransactionLogEntry::TransactionLogEntry(const Customer*& cust) :
   customer_(cust),
   transactionLog_(std::vector<Transaction>())
{
}



//------------------------- Destructor -------------------------------------
// Frees the transaction of any dynamic memory, the transaction does not 
// own the item data -- it does not own the customer, that is to be freed
// by the customer Manager
// Postconditions: frees any deynamic memory associated with the 
//                 transactionLogEntry
TransactionLogEntry::~TransactionLogEntry()
{

   transactionLog_.clear();
   // bc does not own the memory for customer
   customer_ = nullptr;
}


//-------------------------- operator== ------------------------------------
// Checks if two transactionLogEntries are equivilent. Equivilance is 
// defined by the customer name the object stores
// Postconditions: Returns true if both objects are equivilent
//                 Returns false if the objects are not equivilent.
bool TransactionLogEntry::operator==(const Comparable& right) const
{

   const TransactionLogEntry& rightHandSide = static_cast<const TransactionLogEntry&>(right);

   if (customer_ != rightHandSide.customer_) {
      return false;
   }
   // there will never be one without this customer name
   /*
   // may not need this case as it is unlikely to show up
   else if (transactionLog_ != rightHandSide.transactionLog_) {
      return false;
   }
   */
   else {
      return true;
   }
}


//-------------------------- operator!= ------------------------------------
// Checks if two transactionLogEntries are not equivilent. Equivilance is 
// quivilance is defined by the customer name the object stores
// Postconditions: Returns true if both objects are not  equivilent
//                 Returns false if the objects are equivilent.
bool TransactionLogEntry::operator!=(const Comparable& right) const
{
    return !(*this == right);
}


//-------------------------- operator> -------------------------------------
// Checks if two TransactionLogEntries have a greater than relationship. 
// Value is determined by the customer name associated with the entry
// Postconditions: Returns true if the right hand side is smaller
//                 than the left hand side. Otherwise, false is returned
bool TransactionLogEntry::operator>(const Comparable& right) const
{
   const TransactionLogEntry& rightHandSide = static_cast<const TransactionLogEntry&>(right);

   std::string toCompCustName = rightHandSide.customer_->getName();

   if (customer_->getName() < toCompCustName) {
      return false;
   }
   // the size of the transaction log
   else if (transactionLog_.size() < rightHandSide.transactionLog_.size()) {
      return false;
   }
   else {
      return true;
   }
}


//-------------------------- operator< -------------------------------------
// Checks if two TransactionLogEntries have a less than relationship. 
// Value is determined by the customer name associated with the entry
// Postconditions: Returns false if the right hand side is smaller
//                 than the left hand side. Otherwise, true is returned
bool TransactionLogEntry::operator<(const Comparable& right) const
{
   const TransactionLogEntry& rightHandSide = static_cast<const TransactionLogEntry&>(right);

   std::string toCompCustName = rightHandSide.customer_->getName();

   if (customer_->getName() > toCompCustName) {
      return false;
   }
   // the size of the transaction log
   else if (transactionLog_.size() > rightHandSide.transactionLog_.size()) {
      return false;
   }
   else {
      return true;
   }
}


//-------------------------- print --------------------------------------
// Prints the customer name on one line then each transaction in chrono
// order one tab under the customer name
// Postconditions: prints to the console a representation of the object
void TransactionLogEntry::print() const
{
   std::cout << customer_->getName() << std::endl;
   int size = static_cast<int>(transactionLog_.size());

   for (int i = 0; i < size; i++) {

      const Collectible* item = transactionLog_[i].getItemTransacted();
      std::string transactionType = transactionLog_[i].getTransactionType();

      // bc friend access
      //const Comparable* toPrint = static_cast<const Comparable*>(item);

      if (transactionType == "B") {
         transactionType = "Purachased";
      }
      else {
         transactionType = "Sold";
      }

      std::cout << "\t" << transactionType << " " << *item << std::endl;
   }
}



//-------------------------- addTransaction --------------------------------
// Adds a transaction for a given customer to their transactionLog
// Preconditions:   Assumes that the transaction is valid and that the
//                  customer is valid
// Postconditions:  adds the transaction to the end of the customers log
bool TransactionLogEntry::addTransaction(Transaction& toAdd) const
{
   transactionLog_.push_back(toAdd);

   return true;
}


//-------------------------- copy ------------------------------------------
// creates a deep copy of the current entry and returns a non-modifyable
// pointer to it
// preconditions : The caller must means to deallocate the memory
//                 associated
// Postconditions: returns a constant pointer deep copy of the current
//                 entry
const Comparable* TransactionLogEntry::copy() const
{
   const Comparable* newLog = new TransactionLogEntry(*this);
   return newLog;
}
