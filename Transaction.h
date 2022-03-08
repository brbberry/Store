// Blake Berry
// 03/08/2022
// Homework 4
// This file is an interface for the Transaction class. The Transaction class
// wraps a item transacted upon and stores a representation of the transaction
// type. This class then produces a pointer to itself for refrence by other
// classes needing transaction information.
//-----------------------------------------------------------------------------

#pragma once
#include "Collectible.h"

class Transaction
{
private :

   const Collectible* itemTransacted_; // the item a transaction was taken 
                                       // against
   std::string transactionType_; // the type of transaction

public:

   //------------------------ Constructor -------------------------------------
   // Constructs a transaction from a given item and the type of transaction
   // taken
   // Postconditions: couples a item with the transaction that was taken on
   //                 the item
   Transaction(const Collectible*& item, std::string type);


   //------------------------ getItemTransacted -------------------------------
   // returns the item transacted
   // Postconditions: a constant pointer to that item is returned
   const Collectible* getItemTransacted() const;


   //------------------------ getTransactionType ------------------------------
   // returns the type of transaction done on the item
   // Postconditions: returns a string representation of the transaction type
   //                 on the item
   std::string getTransactionType() const;

   //------------------------- Destructor -------------------------------------
   // Frees the transaction of any dynamic memory, the transaction does not 
   // own the item data -- it is to be freed by the itemManager.
   // Postconditions: frees any dynamic memory associated with the transaction
   ~Transaction();
};

