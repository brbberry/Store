// Blake Berry
// 02/22/2022
// Homework 4 design
// This file is an interface for the CustomerManager class. The Customermanager 
//  class stores a hashtable of customers for quick look up based upon a 
// customers customer number. This class is responsible for checking for valid
// customers and returning customer information to those that request it. It 
// is also repsonsible for filling in the stores original customer list
//-----------------------------------------------------------------------------



// assumes that if a customer is not in the customer log that they will not
// be added and that an exception is thrown

// all customers will be initialized from the file only

#pragma once
#include "Customer.h"
#include <iostream>
#include <fstream>

class CustomerManager
{
private:

   HashableObject**  customerLog_;
   int              numCustomers_;

   //-------------------------- CheckCustomerLog ------------------------------
   // Checks if a given customer is in the customer log
   // Postconditions:  If a collectible is found in the store true is returned
   //                  If it is not found an error is thrown
   // Function Calls:  retrieve is called to check the search tree for a given
   //                  comparable
   bool checkCustomerLog(const HashableObject& toGet) const;
   //PSUEDOCODE
   /*
      cast comparable to a customer

   */
   
   std::string processCustomer(std::string& curLine) const;

   int hashCustomer(std::string customerNumber) const;

   bool validCustomerHash(int customerIndex) const;

public:



   //-------------------------- Default Constructor ---------------------------
   // Creates an Item manager with a fully working factory and an empty 
   // inventory
   // Preconditions : The factory must be intialized with the items that are
   //                 allowed in the collections store
   // Postconditions: a new item manager is created
   CustomerManager(int numCustomers = 1000);


   //-------------------------- Destructor -----------------------------------
   // Frees any dynamic memory associated with the items manager class
   // Preconditions : The factory must be capable to freeing its dynamic memory
   //                   
   //                 the items inventory must be capable of freeing its 
   //                 dynamic memory
   // 
   // Postconditions: frees the memory associated with the items manager
   ~CustomerManager();


   //-------------------------- FillCustomerLog -------------------------------
   // Fills the inventory from a file, Coins are index 0, Comics are index 2, 
   // and SportsCards are index 3
   // Preconditions : The factory must be initialized
   // 
   //                 The file must be formatted correctly
   // 
   // Postconditions: The ItemManagers inventory is filled, exceptions are 
   //                 thrown if invalid data is attempted
   void fillCustomerLog(std::ifstream& readFrom);
   // PSUEDOCODE
   /*
      while we are not at the end of the file do
         store first char as a string

         use that string to get a dummy collectible from the factory
         if nullptr is returned
            throw an invalid error and keep processing
         else
            try
               call the collectibles create method on the remainder of
               the string

            catch
               the exception and go to the next line of the file

           if the collectible is in the store
               increase the count
           else
               add call insert to add it to the inventory

   */


   //-------------------------- findCustomer ---------------------------------
   // Given the ID of an item them method handles the sale of an item
   // if the item is present its inventory count is incrimented appropriately
   // Preconditions : the hashable object frees its own dynamically allocated
   //                 memory
   // 
   //                 The factory must be initalized
   // 
   // Postconditions: An item is sold and the inventory is updated and true
   //                 is returned. Throws an error if an invalid item is
   //                 attempted to be sold
   const Customer* findCustomer(std::string ID);
   // PSUEDOCODE
   /*

   */
};

