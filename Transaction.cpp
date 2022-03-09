// Blake Berry
// 03/08/2022
// Homework 4
// This file is an implimentatione for the Transaction class. The Transaction 
// class wraps a item transacted upon and stores a representation of the
//  transaction type. This class then produces a pointer to itself for refrence
//  by other classes needing transaction information.
//-----------------------------------------------------------------------------


#include "Transaction.h"
#include "Coin.h"


//------------------------ Constructor -------------------------------------
// Constructs a transaction from a given item and the type of transaction
// taken
// Postconditions: couples a item with the transaction that was taken on
//                 the item
Transaction::Transaction(const Collectible*& item, std::string type) :
   itemTransacted_(item),
   transactionType_(type)
{
}


//------------------------ getTransactionType ------------------------------
// returns the type of transaction done on the item
// Postconditions: returns a string representation of the transaction type
//                 on the item
std::string Transaction::getTransactionType() const
{
   return transactionType_;
}


//------------------------ getItemTransacted -------------------------------
// returns the item transacted
// Postconditions: a constant pointer to that item is returned
const Collectible* Transaction::getItemTransacted() const
{
   return itemTransacted_;
}


//------------------------- Destructor -------------------------------------
// Frees the transaction of any dynamic memory, the transaction does not 
// own the item data -- it is to be freed by the itemManager.
// Postconditions: frees any dynamic memory associated with the transaction
Transaction::~Transaction()
{
}
