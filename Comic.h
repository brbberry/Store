// Blake Berry
// 03/08/2022
// Homework 4
// This file is an interface for the Comic class. The Comic class inherted
// from the collectible interface. The Comic class represents an item that can
// exist at a collectible store
//-----------------------------------------------------------------------------

#pragma once
#include "Collectible.h"
class Comic : public Collectible
{
private:

   std::string publisher_; // the publisher of the comic
   std::string title_;     // the comics title
   int year_;              // the year the comic was published
   std::string grade_;     // the grade of the comic

public:

   //-------------------------- Constructor -----------------------------------
   // Creates a completely empty comic with empty fields
   // Postconditions: an empty comic is created
   Comic(std::string id = "C");

   //-------------------------- destructor -----------------------------------
   // Frees any dynamic memory associated with the Comic
   // Postconditions: The comic is freed of any dynamic memory
   virtual ~Comic();

   //-------------------------- Create --------------------------------------
   // Parses a given string and created a comic from a given string returning 
   // itself
   // PreConditions : The comic data must be formatted correctly in the string
   // Postconditions: returns a constant pointer to the created Comic
   //                 throws an exception if any of the information is invalid
   virtual const Comic* create(std::string toMakeFrom) const;

   //-------------------------- operator== ------------------------------------
   // Checks if two Comics are equivilent. Equivilance is defined as each 
   // Comic having the same publisher, title year and grade.
   // Postconditions: Returns true if both Comics are equivilent
   //                 Returns false if the Comics are not equivilent.
   virtual bool operator==(const Comparable& right) const;


   //-------------------------- operator!= ------------------------------------
   // Checks if two Comics are not  equivilent. Equivilance is defined as each 
   // Comic having the same publisher, title year and grade.
   // Preconditions : The right hand side comparable must be defined
   // Postconditions: Returns true if both Comics are not equivilent
   //                 Returns false if the Comics are equivilent.
   virtual bool operator!=(const Comparable& right) const;


   //-------------------------- operator> -------------------------------------
   // Checks if two Comics have a greater than relationship. Comics are 
   // weighted such that we first consider them by publisher, then by title,
   // then by year, then by grade. The fields are compared using defined >
   // Postconditions: Returns true if the right hand side comic is smaller
   //                 than the left hand side. Otherwise, false is returned
   virtual bool operator>(const Comparable& right) const;


   //-------------------------- operator< --------------------------------------
   // Checks if two Comics have a less than relationship. Comics are 
   // weighted such that we first consider them by publisher, then by title,
   // then by year, then by grade. The fields are compared using defined <
   // Postconditions: Returns true if the right hand side comic is larger
   //                 than the left hand side. Otherwise, false is returned
   virtual bool operator<(const Comparable& right) const;


   //-------------------------- print --------------------------------------
   // Prints the comics publisher, title, year, and grade on one line
   // Postconditions: prints to the console a representation of the Comic
   virtual void print() const;


   //-------------------------- copy ------------------------------------------
   // creates a deep copy of the current comic and returns a non-modifyable
   // pointer to it
   // preconditions : The caller must means to deallocate the memory
   //                 associated
   // Postconditions: returns a constant pointer deep copy of the current
   //                 comic
   virtual const Comic* copy() const;
};

