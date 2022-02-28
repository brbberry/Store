// Blake Berry
// 02/22/2022
// Homework 4 Design
// This file is an interface for the Collectible class. The collectible
// class is an abstract base class that is hashable due to inheritance from
// the hashable object class. The class lays out behavior for many collectibles
//------------------------------------------------------------------------------

#pragma once
#include "HashableObject.h"
#include "Comparable.h"


/*
has access to

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
   void setKey(std::string id) {
      id_ = id;
   }



*/


class Collectible : public HashableObject, public Comparable
{

protected:

   std::string processConstruction(std::string& instructions) {
      // format {, data} position 2 is the first char of the data
      int startPosition = 2;
      int endPosition = 2;

      if (instructions == "" || startPosition > instructions.length()) {
         return "";
      }

      // format {, data} position 2 is the first char of the data
      while (endPosition < instructions.length() &&
         instructions[endPosition] != ',') {

         endPosition++;
      }

      std::string data;

      if (endPosition == instructions.length()) {
         data = instructions.substr(startPosition, endPosition);
      }
      else {
         data = instructions.substr(startPosition, endPosition - 2);
      }

      // update the instructions to get the next piece of data
      instructions.erase(0, endPosition);
      return data;
   }


public : 
   
   Collectible(std::string type): HashableObject(type) {};

   //-------------------------- operator== ------------------------------------
   // Checks if two Collectibles are equivilent. Equivilance is defined by the 
   // derived class
   // Postconditions: Returns true if both collectibles are equivilent
   //                 Returns false otherwise.
   virtual bool operator==(const Comparable& right) const = 0;


   //-------------------------- operator!= ------------------------------------
   // Checks if two Collectibles are not equivilent. Equivilance is defined by 
   // the  derived class
   // Postconditions: Returns true if both Collectibles are not equivilent
   //                 Returns false otherwise.
   virtual bool operator!=(const Comparable& right) const = 0;


   //-------------------------- operator> -------------------------------------
   // Checks if two Collectibles have a greater than relationship. 
   // Greater than is defined by the  derived class
   // Postconditions: Returns true if the right hand side is smaller
   //                 than the left hand side. Otherwise, false is returned
   virtual bool operator>(const Comparable& right) const = 0;


   //-------------------------- operator< -------------------------------------
   // Checks if two Collectibles have a less than relationship. 
   // GLess than is defined by the  derived class
   // Postconditions: Returns true if the right hand side is larger
   //                 than the left hand side. Otherwise, false is returned
   virtual bool operator<(const Comparable& right) const = 0;


   //-------------------------- destructor -----------------------------------
   // Frees any dynamic memory associated with the Collectible
   // Postconditions: The Collectible Object is freed of any dynamic memory
   virtual ~Collectible() {};


   //-------------------------------- Hash -----------------------------------
   // generates an int from the value that the Collectible holds
   // Postconditions: an integer is returned based off the value held by the 
   //                 Collectible object
   virtual int hash() const {
      std::string comparableType = HashableObject::getID();
      return comparableType[0] - 'A';
   };


   //-------------------------- print -----------------------------------------
   // Prints the Collectible as defined by the dervied classes
   // Postconditions: prints to the console a representation of the Collectible
   virtual void print() const = 0;


   //-------------------------- Create --------------------------------------
   // creates a Collectible from a given string returning itself
   // PreConditions : It is assumed that the collectible type is valid
   // Postconditions: returns a constant pointer to the created collectible
   virtual const Collectible* create(std::string toMakeFrom) = 0;
};

