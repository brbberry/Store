// Blake Berry
// 03/08/2022
// Homework 4
// This file is an implimentation for the Customer class. The Customer class 
// represents a store customer and has an associated name and customer number
// the customer is hashable
//-----------------------------------------------------------------------------


#include "Customer.h"


//-------------------------- Constructor -----------------------------------
// Creates a customer given a number and a string name. 
// Preconditions : It is assumed that the customer number is 3 digits
// Postconditions: A customer is created with a given customer number
//                 and a given customer name
Customer::Customer(int customerNumber, std::string customerName) :
   HashableObject(std::to_string(customerNumber)),
   customerNumber_(customerNumber),
   customerName_(customerName)
{
}




//-------------------------- getName -----------------------------------
// Returns the name associated with the customer
// Postconditions: returns the name associated with the customer
std::string Customer::getName() const
{
   return customerName_;
}