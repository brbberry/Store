#include "Transaction.h"
#include "Coin.h"
Transaction::Transaction(const Collectible*& item, std::string type) :
   itemTransacted_(item),
   transactionType_(type)
{
}

std::string Transaction::getTransactionType() const
{
   return transactionType_;
}

const Collectible* Transaction::getItemTransacted() const
{

   return itemTransacted_;
}

Transaction::~Transaction()
{
   itemTransacted_ = nullptr;
}
