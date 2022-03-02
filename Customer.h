// Blake Berry
// 02/22/2022
// Homework 4 design
// This file is an interface for the Customer class. The Customer class 
// represents a store customer and has an associated name and customer number
// the customer is hashable
//-----------------------------------------------------------------------------

#pragma once
#include "HashableObject.h"
#include <string>

//HAS ACCESS TO
/*
   //-------------------------------- getID ----------------------------------
   // returns the held string ID
   // Postconditions: the string ID is returned
   std::string getID() const {
      return id_;
   }

   //--------------------------- getDeleted -------------------------------
   // returns the bool is a hashable object is deleted
   // Postconditions: the deleted bool is returned
   bool getDeleted() const {
      return deleted_;
   }


   //------------------------------- setID -----------------------------------
   // sets the hashable objects ID to that of the string passed in
   // Postconditions: the hashable object ID is set
   void setID(std::string id) {
      id_ = id;
   }


*/


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


   //-------------------------------- Hash -----------------------------------
   // generates an int from the value that the HashableObject holds
   // Preconditions : Assumes that the customer number is 3 digits
   // Postconditions: an integer is returned based off the value held by the 
   //                 hashable object
   virtual int hash() const;
   //PSUEDOCDOE
   /*
      return customerNumber_
   
   */

   std::string getName() const;

};

