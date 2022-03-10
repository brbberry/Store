// Blake Berry
// 01/10/2022
// Homework 1
// This file lays out the functionality of the comparable class. The comparable 
// class holds a single character and standard operations of the char class
// can be used.
//------------------------------------------------------------------------------
#pragma once
#include <iostream>

class Comparable
{

public:

   //-------------------------- destructor --------------------------------------
   // Frees any comparable dynamic memory
   // Postconditions: frees the comparable of any dynamic memory
   virtual ~Comparable() {};

   //-------------------------- operator== --------------------------------------
   // Checks if two comparables are equivilent. Equivilance is defined as each 
   // comparable storing the same character
   // Preconditions : The right hand side comparable must be defined
   // Postconditions: Returns true if both comparables are equivilent
   //                 Returns false if the comparables are not equivilent.
   virtual bool operator==(const Comparable& right) const = 0;


   //-------------------------- operator!= --------------------------------------
   // Checks if two comparables are not equivilent. Equivilance is defined as each 
   // comparable storing the same valued primative
   // Preconditions : The right hand side comparable must be defined
   // Postconditions: Returns true if both comparables are not  equivilent
   //                 Returns false if the comparables are equivilent.
   virtual bool operator!=(const Comparable& right) const = 0;


   //-------------------------- operator> --------------------------------------
   // Checks if two comparables are equivilent. Value is determined by the ascii
   // value of the held comparable
   // Preconditions : The right hand side comparable must be defined
   // Postconditions: Returns true if the right hand side comparable is smaller
   //                 than the left hand side. Otherwise, false is returned
   virtual bool operator>(const Comparable& right) const = 0;


   //-------------------------- operator< --------------------------------------
   // Checks if two comparables are equivilent. Value is determined by the ascii
   // value of the held comparable
   // Preconditions : The right hand side comparable must be defined
   // Postconditions: Returns fakse if the right hand side comparable is smaller
   //                 than the left hand side. Otherwise, true is returned
   virtual bool operator<(const Comparable& right) const = 0;


   //-------------------------- copy ------------------------------------------
   // creates a deep copy of the current comparable and returns a 
   // non-modifyable pointer to it
   // preconditions : The caller must means to deallocate the memory
   //                 associated
   // Postconditions: returns a constant pointer deep copy of the current
   //                 comparable
   virtual const Comparable* copy() const = 0;

   //-------------------------- print --------------------------------------
   // Prints the comparable as defined by the dervied classes
   // Postconditions: prints to the console a representation of the comparable
   virtual void print() const = 0;

   
   //-------------------------- operator<< ---------------------------------------
   // Streams the comparable out listing the held comparable. A single char.
   // Preconditions : The comparable to be stream out must be defined
   //                 The output stream must be defined
   // Postconditions:  outputs the comparable as a signle char to the output
   friend std::ostream& operator<<(std::ostream& output, const Comparable& toStream) {
     toStream.print();
     return output;
   }
   
};
