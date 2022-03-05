// Blake Berry
// 02/22/2022
// Homework 4 Design
// This file is an interface for the Coin class. The Coin class inherted
// from the collectible interface. The Coin class represents an item that can
// exist at a collectible store
//-----------------------------------------------------------------------------

#pragma once
#include "Collectible.h"

class Coin : public Collectible
{

private:

   int year_;         // the year the coin originated from
   int grade_;        // the coins grade
   std::string type_; // the string type the coin is

   //int count_;        // the number of this coin


public:

   //-------------------------- Constructor -----------------------------------
   // Creates a completely empty coin with empty fields
   // Postconditions: an empty coin is created
   Coin(std::string type = "M");


   //-------------------------- destructor -----------------------------------
   // Frees any dynamic memory associated with the Coin
   // Postconditions: The coin is freed of any dynamic memory
   virtual ~Coin();

   //-------------------------- Create --------------------------------------
   // Parses a given string and created a coin from a given string returning 
   // itself
   // PreConditions : The coin data must be formatted correctly in the string
   // Postconditions: returns a constant pointer to the created Coin
   //                 throws an exception if any of the information is invalid
   virtual const Coin* create(std::string toMakeFrom) const;

   //-------------------------- operator== --------------------------------------
   // Checks if two Coins are equivilent. Equivilance is defined as each 
   // Coin having the sametype year and grade
   // Postconditions: Returns true if both Coins are equivilent
   //                 Returns false if the Coins are not equivilent.
   virtual bool operator==(const Comparable& right) const;


   //-------------------------- operator!= --------------------------------------
   // Checks if two Coins are not equivilent. Equivilance is defined as each 
   // Coin having the sametype year and grade
   // Postconditions: Returns true if both Coins are not  equivilent
   //                 Returns false if the Coins are equivilent.
   virtual bool operator!=(const Comparable& right) const;


   //-------------------------- operator> --------------------------------------
   // Checks if two Coins have a greater than relationship. Coins are weighted
   // such that we first consider them by type, then by year, then by grade.
   // The string type is compared then the following ints
   // Postconditions: Returns true if the right hand side coin is smaller
   //                 than the left hand side. Otherwise, false is returned
   virtual bool operator>(const Comparable& right) const;


   //-------------------------- operator< --------------------------------------
   // Checks if two Coins have a less than relationship. Coins are weighted
   // such that we first consider them by type, then by year, then by grade.
   // The string type is compared then the following ints
   // Postconditions: Returns false if the right hand side Coin is smaller
   //                 than the left hand side. Otherwise, true is returned
   virtual bool operator<(const Comparable& right) const;


   //-------------------------------- Hash -----------------------------------
   // generates an int from the value that the HashableObject holds
   // Preconditions : Assumes that the key is a capital ASCII value A-Z
   // Postconditions: an integer is returned based off the value held by the 
   //                 hashable object
   virtual int hash() const;
   //PSUEDOCODE
   /*
   
      Subtracts ASCII for A from the given string version of the comparable
   
   */


   //-------------------------- print --------------------------------------
   // Prints the coins type year and grade on one line
   // Postconditions: prints to the console a representation of the Coin
   virtual void print() const;

   virtual const Coin* copy() const;


};

