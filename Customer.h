// Blake Berry
// 03/08/2022
// Homework 4
// This file is an interface for the Customer class. The Customer class 
// represents a store customer and has an associated name and customer number
// the customer is hashable
//-----------------------------------------------------------------------------

#pragma once
#include "HashableObject.h"
#include <string>


class Customer : public HashableObject
{
private:

   int         customerNumber_;  // the customer number associated with the 
                                 // customer object serving as a hashKey

   std::string customerName_;   // the customer name associated with the 
                                // customer object

public:

   //-------------------------- Constructor -----------------------------------
   // Creates a customer given a number and a string name. 
   // Preconditions : It is assumed that the customer number is 3 digits
   // Postconditions: A customer is created with a given customer number
   //                 and a given customer name
   Customer(int customerNumber = 0, std::string customerName = "");

   //-------------------------- destructor -----------------------------------
   // Frees any dynamic memory associated with the HashableObject
   // Postconditions: The hashable Object is freed of any dynamic memory
   virtual ~Customer() {};

   //-------------------------- getName -----------------------------------
   // Returns the name associated with the customer
   // Postconditions: returns the name associated with the customer
   std::string getName() const;
};

