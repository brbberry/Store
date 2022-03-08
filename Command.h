// Blake Berry
// 02/22/2022
// Homework 4 design
// This file is an interface for the Command class. The Command class is an 
//  abstract baseclass for commands that can be executed in a store. The 
// command is hashable and allows those derived to define how they execute
// their command
//-----------------------------------------------------------------------------

#pragma once
#include "HashableObject.h"
#include <string>
#include "TransactionManager.h"
#include "CustomerManager.h"
#include "ItemsManager.h"


class Command : public HashableObject
{

protected:

   //-------------------------getCustomer -------------------------------------
   // Returns a string of the customers number from a given command to process
   // preconditions : Assumes the customer number is the first data and that
   //                 it is 3 digits long
   //                 
   //                 assumes format ", XXX" where XXX is cust #
   // Postconditions: The customer number is returned in string for,
   //                 if an invalid customer number if found an empty string
   //                 is returned
   std::string getCustomer(std::string& command) const {

      // for getting customer number get rid of ", "
      command.erase(0, 2);

      std::string custNum = command.substr(0, 3);
      bool allDigits = true;
      int custNumSize = custNum.size();

      for (int i = 0; i < custNumSize; i++) {
         allDigits = std::isdigit(custNum[i]);
         if (!allDigits) {
            custNum = "";
         }
      }

      // gets rid of "XXX, "
      command.erase(0, 5);
      return custNum;
   }

public:

   //-------------------------- Constructor -----------------------------------
   // Initializes the key in the hashable object class for a given command
   // postconditions : Assigns a key for a given command object
   Command(std::string key = "") : HashableObject(key) {};


   //-------------------------- destructor -----------------------------------
   // Frees any dynamic memory associated with the command objects
   // Postconditions: The command is freed of any dynamic memory
   virtual ~Command() {};


   //-------------------------- Execute -----------------------------------
   // Creates a specific Command based off a string type that is stored
   // in the command class's field
   // Postconditions: The command object is created
   virtual void execute(TransactionManager*& tManager,
                        ItemsManager*& iManager,
                        CustomerManager*& cManager,
                        std::string& command) const = 0;

};

