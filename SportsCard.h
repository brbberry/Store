// Blake Berry
// 02/22/2022
// Homework 4 Design
// This file is an interface for the SportsCard class. The SportsCard class
// Inherited from the collectible interface. The Comic class represents an item
//  that can exist at a collectible store
//-----------------------------------------------------------------------------

#pragma once
#include "Collectible.h"

class SportsCard : public Collectible
{
private:

   std::string player_;       // the name of the baseball player
   std::string manufacturer_; // the card manufacturer
   int year_;                 // the year the cards from
   std::string grade_;        // the grade of the card


public:

   //-------------------------- Constructor -----------------------------------
   // Creates a completely empty SportsCard with empty fields
   // Postconditions: an empty SportsCard is created
   SportsCard(std::string key = "S");

   //-------------------------- destructor -----------------------------------
   // Frees any dynamic memory associated with the SportsCard
   // Postconditions: The SportsCard is freed of any dynamic memory
   virtual ~SportsCard();

   //-------------------------- Create --------------------------------------
   // Parses a given string and created a SportsCard from a given string 
   // returning  itself
   // PreConditions : The SportsCard data must be formatted correctly in the
   //                 string
   // Postconditions: returns a constant pointer to the created SportsCard
   //                 throws an exception if any of the information is invalid
   virtual const SportsCard* create(std::string toMakeFrom);


   //-------------------------- operator== ------------------------------------
   // Checks if two SportsCards are equivilent. Equivilance is defined as each 
   // Comic having the same player, manufacturer, year, and grade
   // Postconditions: Returns true if both SportsCards are equivilent
   //                 Returns false if the SportsCards are not equivilent.
   virtual bool operator==(const Comparable& right) const;


   //-------------------------- operator!= --------------------------------------
   // Checks if two SportsCards are not equivilent. Equivilance is defined as each 
   // Comic having the same player, manufacturer, year, and grade
   // Postconditions: Returns true if both SportsCards are not equivilent
   //                 Returns false if the SportsCards are equivilent.
   virtual bool operator!=(const Comparable& right) const;


   //-------------------------- operator> -------------------------------------
   // Checks if two SportsCards have a greater than relationship. SportsCards
   //  are weighted such that we first consider them by player, then by
   // manufacturer, then by year, then by grade. 
   // The fields are compared using defined >
   // Postconditions: Returns true if the right hand side SportsCard is smaller
   //                 than the left hand side. Otherwise, false is returned
   virtual bool operator>(const Comparable& right) const;


   //-------------------------- operator< --------------------------------------
   // Checks if two SportsCards have a less than relationship. SportsCards
   //  are weighted such that we first consider them by player, then by
   // manufacturer, then by year, then by grade. 
   // The fields are compared using defined <
   // Postconditions: Returns true if the right hand side SportsCard is larger
   //                 than the left hand side. Otherwise, false is returned
   virtual bool operator<(const Comparable& right) const;


   //-------------------------------- Hash -----------------------------------
   // generates an int from the value that the SportsCard holds
   // Preconditions : Assumes that the key is a capital ASCII value A-Z
   // Postconditions: an integer is returned based off the value held by the 
   //                 hashable object
   virtual int hash() const;
   //PSUEDOCODE
   /*

      Subtracts ASCII for A from the given string version of the comparable

   */


   //-------------------------- print ----------------------------------------
   // Prints the SportsCard player, manufacturer, year, and grade on one line
   // Postconditions: prints to the console a representation of the SportsCard
   virtual void print() const;
};

