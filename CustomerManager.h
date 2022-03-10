// Blake Berry
// 03/08/2022
// Homework 4
// This file is an interface for the CustomerManager class. The Customermanager 
//  class stores a hashtable of customers for quick look up based upon a 
// customers customer number. This class is responsible for checking for valid
// customers and returning customer information to those that request it. It 
// is also repsonsible for filling in the stores original customer list
//-----------------------------------------------------------------------------

#pragma once
#include "Customer.h"
#include <iostream>
#include <fstream>
#include <ctype.h>
#include "CollectiblesStoreError.h"
#include <vector>

class CustomerManager
{
private:

   static const int NUM_CUSTOMERS = 1000; // cannot be fewer than 1

   HashableObject**  customerLog_; // hashtable with customer objects


   //------------------- validCustomerNumber ----------------------------------
   // Checks if a string represtation of an item is valid
   // Postconditions: returns true if the customer number is valid and returns
   //                 false otherwise
   bool validCustomerNumber(std::string custNum) const;

   //------------------- Process Customer ------------------------------------
   // Parses a given input string returning data from a customer
   // PreConditions : The input must be comma space seperated
   // Postconditions: returns a string representation of the data following
   //                 the comma
   std::string processCustomer(std::string& curLine) const;


   //------------------- hashCustomer ------------------------------------
   // Returns an integer hash from a customer's key, their customer number
   // PreConditions : The customer number must be valid
   // Postconditions: returns a string representation of the data following
   //                 the comma
   int hashCustomer(std::string customerNumber) const;


   //--------------------- validCustomerHash --------------------------------
   // Checks if the hash is in the correct range
   // Postconditions: returns true if the hash is in range and false otherwise
   bool validCustomerHash(int customerIndex) const;

public:


   //-------------------------- Default Constructor ---------------------------
   // Creates a customerManager capable of tracking NUM_CUSTOMER customers
   // Preconditions : the NUM_CUSTOMERS must be greater than 1
   // Postconditions: a new customer manager is created 
   CustomerManager();


   //-------------------------- Destructor -----------------------------------
   // Frees any dynamic memory associated with the customer manager class
   // Preconditions : the customer must be capable of freeing its own 
   //                 dynamic memory
   // Postconditions: frees the memory associated with the customer manager
   ~CustomerManager();


   //-------------------------- FillCustomerLog -------------------------------
   // Fills the customer log from a given file. If any information is invalid
   // an error is thrown to the cout and the file continues to be processed
   // Preconditions : Assumes no two customers are in the file with the same
   //                 customer number
   // Postconditions: The customer list is filled from the file and any errors
   //                 are thrown to cout
   void fillCustomerLog(std::ifstream& readFrom);


   //-------------------------- findCustomer ---------------------------------
   // Given the customer ID the customer manager will find a customer in the
   // customer list
   // 
   // Postconditions: If the customer is found it is returned to the caller
   //                 if the customer id is invalid or the customer cannot
   //                 be found an error is thrown
   const Customer* findCustomer(std::string ID);
};

