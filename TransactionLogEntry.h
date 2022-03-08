// Blake Berry
// 03/08/2022
// Homework 4
// This file is an interface for the TransactionLogEntry class. The 
// TransactionLogEntry class is a sortable class that sorts based upon the
// customer name. The TransactionLogEntry class couples a customer with a list
// of transactions made by that customer. These transactions are stored in 
// chronlogical order
//-----------------------------------------------------------------------------

#pragma once
#include "Comparable.h"
#include "Collectible.h"
#include "Customer.h"
#include <vector>
#include "Transaction.h"

class TransactionLogEntry: public Comparable
{

private:

   const Customer* customer_; // the customer making the transaction
   mutable std::vector<Transaction> transactionLog_; // a chronological order of
                                             // the customers transactions

public:

   //-------------------------- Default Constructor ---------------------------
   // Creates an empty entry filled with a null customer and empty transition
   // log
   // Postconditions: Creates an empty entry filled with a null customer and empty 
   // transition log
   TransactionLogEntry();

   //-------------------------- Constructor -----------------------------------
   // Creates a log entry given a customer and an initial transaction
   // Postconditions: Creates an entry for a given customer and logs the
   //                 transaction
   TransactionLogEntry(const Customer*& cust, Transaction& initialTransaction);

   
   //-------------------------- Constructor -----------------------------------
   // Creates a dummy transitionLogEntry for a given customer
   // Postconditions: Creates an entry for a given customer
   TransactionLogEntry(const Customer*& cust);
   

   //------------------------- Destructor -------------------------------------
   // Frees the transaction of any dynamic memory, the transaction does not 
   // own the item data -- it does not own the customer, that is to be freed
   // by the customer Manager
   // Postconditions: frees any deynamic memory associated with the 
   //                 transactionLogEntry
   ~TransactionLogEntry();

   //-------------------------- operator== ------------------------------------
   // Checks if two transactionLogEntries are equivilent. Equivilance is 
   // defined by the customer name the object stores
   // Postconditions: Returns true if both objects are equivilent
   //                 Returns false if the objects are not equivilent.
   virtual bool operator==(const Comparable& right) const;


   //-------------------------- operator!= ------------------------------------
   // Checks if two transactionLogEntries are not equivilent. Equivilance is 
   // quivilance is defined by the customer name the object stores
   // Postconditions: Returns true if both objects are not  equivilent
   //                 Returns false if the objects are equivilent.
   virtual bool operator!=(const Comparable& right) const;


   //-------------------------- operator> -------------------------------------
   // Checks if two TransactionLogEntries have a greater than relationship. 
   // Value is determined by the customer name associated with the entry
   // Postconditions: Returns true if the right hand side is smaller
   //                 than the left hand side. Otherwise, false is returned
   virtual bool operator>(const Comparable& right) const;


   //-------------------------- operator< -------------------------------------
   // Checks if two TransactionLogEntries have a less than relationship. 
   // Value is determined by the customer name associated with the entry
   // Postconditions: Returns false if the right hand side is smaller
   //                 than the left hand side. Otherwise, true is returned
   virtual bool operator<(const Comparable& right) const;


   //-------------------------- print --------------------------------------
   // Prints the customer name on one line then each transaction in chrono
   // order one tab under the customer name
   // Postconditions: prints to the console a representation of the object
   virtual void print() const;


   //-------------------------- addTransaction --------------------------------
   // Adds a transaction for a given customer to their transactionLog
   // Preconditions:   Assumes that the transaction is valid and that the
   //                  customer is valid
   // Postconditions:  adds the transaction to the end of the customers log
   bool addTransaction(Transaction& toAdd) const;


   //-------------------------- copy ------------------------------------------
   // creates a deep copy of the current entry and returns a non-modifyable
   // pointer to it
   // preconditions : The caller must means to deallocate the memory
   //                 associated
   // Postconditions: returns a constant pointer deep copy of the current
   //                 entry
   virtual const Comparable* copy() const;
};
