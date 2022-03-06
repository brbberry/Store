// Blake Berry
// 02/22/2022
// Homework 4 design
// This file is an interface for the TransactionManager class. The 
//  TransactionManager stores customers and their purchase history for the 
// collectibles store. The transactionManager does not own the memory to the
// customer or the items in the transaction it simply logs and can provide
// hisotrical information about a csutomers or the stores transaction history
//-----------------------------------------------------------------------------

#pragma once
#include "SearchTree.h"
#include "Customer.h"
#include "Transaction.h"
#include "TransactionLogEntry.h"


class TransactionManager
{
private:

   // search tree filled with TransactionLogEntry items
   SearchTree* transactionHistory_;

public:

   //-------------------------- TransactionManager ----------------------------
   // creates a transaction manager that is empty of transaction to manage
   // Postconditions: creates a transaction manager that is empty of 
   //                 transactions
   TransactionManager();


   //------------------------- Destructor ----------------------------
   // Frees the transactionHistory tree of its nodes
   // Preconditions : Assumes that the collectibles and customers free their
   //                 own dynamic memory
   // Postconditions: Frees the memory associated with the transactionManager
   ~TransactionManager();


   //------------------------- logTransaction ----------------------------
   // Given a customer, item, and transaction type a transaction object is 
   // created and stored in the transaction history
   // Preconditions : Assumes that the collectibles and customers free their
   //                 own dynamic memory
   // Postconditions: Frees the memory associated with the transactionManager
   bool logTransaction(const Customer*& responsible, 
                       const Collectible*& item, 
                       std::string transactionType);

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


   //------------------------- DisplayTransactionHistory ----------------------
   // Traverses the transaction history tree and prints out all of the 
   // customers in alphebtic order and prints their transaction in chrological
   // order
   // Preconditions : Assumes that the print method exists for TransactionEntry
   // Postconditions: prints to the console the transaction history for each 
   //                 customer. Each transaction will appear on one line
   //                 indented by a tab under the customers name
   void displayTransactionHistory() const;


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
   void displayCustomersHistroy(const Customer*& responsible) const;
   //PSUEDOCODE
   /*
      create a dummy transitionLogEntry give the customer
      searches the tree to see if the customer is in the tree

      if the search is successful
         print the transaction
      else
         throw an error that that customer has not transacted
   */

};

