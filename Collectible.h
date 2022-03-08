// Blake Berry
// 03/08/2022
// Homework 4
// This file is an interface for the Collectible class. The collectible
// class is an abstract base class that is hashable due to inheritance from
// the hashable object class. The class lays out behavior for many collectibles
//------------------------------------------------------------------------------

#pragma once
#include "HashableObject.h"
#include "Comparable.h"
#include "CollectiblesStoreError.h"


class Collectible : public HashableObject, public Comparable
{

protected:

   //------------------- Process Construction -------------------------------
   // Parses a given input string returning the data after a comma in an
   // input string
   // PreConditions : The input must be comma seperated and begin with
   //                 ", " a comma and a space
   // Postconditions: returns a string representation of the data following
   //                 the comma
   std::string processConstruction(std::string& instructions) const {

      // format {, data} position 2 is the first char of the data
      int startPosition = 2;
      int endPosition = 2;

      // length of instructions
      int instructionsLength = instructions.length();

      // check if input string is valid
      if (instructions == "" || startPosition > instructionsLength) {
         return "";
      }

      // format {, data} position 2 is the first char of the data
      while (endPosition < instructionsLength &&
         instructions[endPosition] != ',') {

         endPosition++;
      }

      std::string data;

      // if we are at the end, take the rest
      if (endPosition == instructionsLength) {
         data = instructions.substr(startPosition, endPosition);
      }
      // -2 to subtract from the initial start poisiton of 2
      else {
         data = instructions.substr(startPosition, endPosition - 2);
      }

      // update the instructions to get the next piece of data
      instructions.erase(0, endPosition);

      return data;
   }


public:


   //-------------------------- Constructor ------------------------------------
   // Initilizes the hashable object key field
   // Postconditions: sets the key for the hashable collectible
   Collectible(std::string type = "") : HashableObject(type) {};


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


   //-------------------------- print -----------------------------------------
   // Prints the Collectible as defined by the dervied classes
   // Postconditions: prints to the console a representation of the Collectible
   virtual void print() const = 0;


   //-------------------------- Create --------------------------------------
   // creates a Collectible from a given string returning itself
   // PreConditions : It is assumed that the collectible type is valid
   // Postconditions: returns a constant pointer to the created collectible
   virtual const Collectible* create(std::string toMakeFrom) const = 0;


   //-------------------------- Copy --------------------------------------
   // creates a constant deep copy of itself returning it to the caller
   // PreConditions : It is assumed that the caller will manage the memory
   // Postconditions: a constant deep copied pointer to that collectible is
   //                 returned
   virtual const Collectible* copy() const = 0;
};