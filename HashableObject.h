// Blake Berry
// 02/22/2022
// Homework 4 Design
// This file is an interface for the HashableObject class. This class is an
// abstract base class definig the necessary functionality of a hashable obj.
// The class includes a string key and leaves the derived classes to assign
// a value associated with a string key. The hashable object should be able to
// generate its own hash and return both the key and value.
//------------------------------------------------------------------------------

// use key instead of id
#pragma once
#include <string>

class HashableObject
{
private:

   std::string id_;        // the string id held by the hashable object

public:

   //-------------------------- Constructor -----------------------------------
   // Frees any dynamic memory associated with the HashableObject
   // Postconditions: The hashable Object is freed of any dynamic memory
   HashableObject(std::string id = "") : id_(id) {};

   //-------------------------- destructor -----------------------------------
   // Frees any dynamic memory associated with the HashableObject
   // Postconditions: The hashable Object is freed of any dynamic memory
   virtual ~HashableObject() {};





   //-------------------------------- getID ----------------------------------
   // returns the held string ID
   // Postconditions: the string ID is returned
   std::string getID() const {
      return id_;
   }

   //------------------------------- setID -----------------------------------
   // sets the hashable objects ID to that of the string passed in
   // Postconditions: the hashable object ID is set 
   void setID(std::string id) {
      id_ = id;
   }
};
