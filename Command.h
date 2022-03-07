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
#include "StoreCommandFactroy.h"
#include "ItemsManager.h"

/*
HAS ACCESS TO FROM HASHABLEOBJECT
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


class Command : public HashableObject
{

public:

   Command(std::string key = "") : HashableObject(key) {};

   //-------------------------- destructor -----------------------------------
   // Frees any dynamic memory associated with the command objects
   // Postconditions: The command is freed of any dynamic memory
   virtual ~Command() {};


   //-------------------------------- Hash -----------------------------------
   // generates an int from the value that the Command holds
   // Postconditions: an integer is returned based off the value held by the 
   //                 command object
   int hash() const = 0;

   /*
   //-------------------------- Create -----------------------------------
   // Creates a specific Command based off a string type that is stored
   // in the command class's field
   // Postconditions: The command object is created
   virtual const Command* create(std::string type) = 0;
   */

   //-------------------------- Execute -----------------------------------
   // Creates a specific Command based off a string type that is stored
   // in the command class's field
   // Postconditions: The command object is created
   virtual void execute(TransactionManager& tManager,
                        ItemsManager& iManager,
                        CustomerManager& cManager,
                        std::string command) const = 0;

};

