#include "TransactionLogEntry.h"

TransactionLogEntry::TransactionLogEntry() :
   customer_(nullptr),
   transactionLog_(std::vector<Transaction>())
{
}

TransactionLogEntry::TransactionLogEntry(const Customer*& cust, Transaction& initialTransaction) :
   customer_(cust),
   transactionLog_(std::vector<Transaction>())
{
   transactionLog_.push_back(initialTransaction);
}


TransactionLogEntry::TransactionLogEntry(const Customer*& cust) :
   customer_(cust),
   transactionLog_(std::vector<Transaction>())
{
}


TransactionLogEntry::~TransactionLogEntry()
{
   int size = static_cast<int>(transactionLog_.size());

   transactionLog_.clear();
   customer_ = nullptr;

}

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

bool TransactionLogEntry::operator!=(const Comparable& right) const
{
    return !(*this == right);
}

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

void TransactionLogEntry::print() const
{
   std::cout << customer_->getName() << std::endl;
   int size = static_cast<int>(transactionLog_.size());

   for (int i = 0; i < size; i++) {

      const Collectible* item = transactionLog_[i].getItemTransacted();
      std::string transactionType = transactionLog_[i].getTransactionType();

      if (transactionType == "B") {
         transactionType = "Purachased";
      }
      else {
         transactionType = "Sold";
      }

      std::cout << "\t" << transactionType << " " << item << std::endl;
   }
}


bool TransactionLogEntry::addTransaction(Transaction& toAdd) const
{
   Transaction copiedToAdd(toAdd);
   transactionLog_.push_back(copiedToAdd);

   return true;
}

const Comparable* TransactionLogEntry::copy() const
{
   const Comparable* newLog = new TransactionLogEntry(*this);
   return newLog;
}
