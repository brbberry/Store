// Blake Berry
// 03/08/2022
// Homework 4
// This file is an implimentation for the SportsCard class. The SportsCard 
// class Inherited from the collectible interface. The Comic class represents
//   an item that can exist at a collectible store
//-----------------------------------------------------------------------------

#include "SportsCard.h"


//-------------------------- Constructor -----------------------------------
// Creates a completely empty SportsCard with empty fields
// Postconditions: an empty SportsCard is created
SportsCard::SportsCard(std::string key) :
   Collectible(key),
   player_(""),
   manufacturer_(""),
   year_(0),                
   grade_("")
{
}


//-------------------------- destructor -----------------------------------
// Frees any dynamic memory associated with the SportsCard
// Postconditions: The SportsCard is freed of any dynamic memory
SportsCard::~SportsCard()
{
}


//-------------------------- Create --------------------------------------
// Parses a given string and created a SportsCard from a given string 
// returning  itself
// PreConditions : The SportsCard data must be formatted correctly in the
//                 string
// Postconditions: returns a constant pointer to the created SportsCard
//                 throws an exception if any of the information is invalid
const SportsCard* SportsCard::create(std::string toMakeFrom) const
{
   SportsCard* dummy = new SportsCard();
   // assumes that year comes first

   dummy->year_ = std::stoi(Collectible::processConstruction(toMakeFrom));

   if (dummy->year_ < 1000 || dummy->year_ > 2022) {
      //throw error
   }

   // assumes grade comes second
   dummy->grade_ = Collectible::processConstruction(toMakeFrom);
   /*
   if (dummy->grade_ < 0) {
      //throw error
   }
   */

   dummy->player_ = Collectible::processConstruction(toMakeFrom);

   dummy->manufacturer_ = Collectible::processConstruction(toMakeFrom);

   return dummy;
}


//-------------------------- operator== ------------------------------------
// Checks if two SportsCards are equivilent. Equivilance is defined as each 
// Comic having the same player, manufacturer, year, and grade
// Postconditions: Returns true if both SportsCards are equivilent
//                 Returns false if the SportsCards are not equivilent.
bool SportsCard::operator==(const Comparable& right) const
{
   const SportsCard& toCheck = static_cast<const SportsCard&>(right);
   bool equiv = true;
   if (player_ != toCheck.player_) {
      return false;
   }
   if (year_ != toCheck.year_) {
      return false;
   }
   if (manufacturer_ != toCheck.manufacturer_) {
      return false;
   }
   if (grade_ != toCheck.grade_) {
      return false;
   }
   return equiv;
}


//-------------------------- operator!= --------------------------------------
// Checks if two SportsCards are not equivilent. Equivilance is defined as each 
// Comic having the same player, manufacturer, year, and grade
// Postconditions: Returns true if both SportsCards are not equivilent
//                 Returns false if the SportsCards are equivilent.
bool SportsCard::operator!=(const Comparable& right) const
{
   return !((*this) == right);
}


//-------------------------- operator> -------------------------------------
// Checks if two SportsCards have a greater than relationship. SportsCards
//  are weighted such that we first consider them by player, then by
// manufacturer, then by year, then by grade. 
// The fields are compared using defined >
// Postconditions: Returns true if the right hand side SportsCard is smaller
//                 than the left hand side. Otherwise, false is returned
bool SportsCard::operator>(const Comparable& right) const
{

   const SportsCard& toCheck = static_cast<const SportsCard&>(right);

   if (player_ > toCheck.player_) {
      return true;
   }
   else if (player_ == toCheck.player_) {
      if (year_ > toCheck.year_) {
         return true;
      }
      else if (year_ == toCheck.year_) {
         if (manufacturer_ > toCheck.manufacturer_) {
            return true;
         }
         else if(manufacturer_ == toCheck.manufacturer_){
            if (grade_ >toCheck.grade_) {
               return true;
            }
         }
      }
   }

   return false; 
}


//-------------------------- operator< --------------------------------------
// Checks if two SportsCards have a less than relationship. SportsCards
//  are weighted such that we first consider them by player, then by
// manufacturer, then by year, then by grade. 
// The fields are compared using defined <
// Postconditions: Returns true if the right hand side SportsCard is larger
//                 than the left hand side. Otherwise, false is returned
bool SportsCard::operator<(const Comparable& right) const
{

   const SportsCard& toCheck = static_cast<const SportsCard&>(right);
   if (player_ < toCheck.player_) {
      return true;
   }
   else if (player_ == toCheck.player_) {
      if (year_ < toCheck.year_) {
         return true;
      }
      else if (year_ == toCheck.year_) {
         if (manufacturer_ < toCheck.manufacturer_) {
            return true;
         }
         else if(manufacturer_ == toCheck.manufacturer_){
            if (grade_ < toCheck.grade_) {
               return true;
            }
         }
      }
   }

   return false;

}


//-------------------------- print ----------------------------------------
// Prints the SportsCard player, manufacturer, year, and grade on one line
// Postconditions: prints to the console a representation of the SportsCard
void SportsCard::print() const
{
   std::cout << "Sports Card : " << year_ << ", " << grade_ << ", " + manufacturer_
      << ", " + player_;
}


//-------------------------- copy ------------------------------------------
// creates a deep copy of the current coin and returns a non-modifyable
// pointer to it
// preconditions : The caller must means to deallocate the memory
//                 associated
// Postconditions: returns a constant pointer deep copy of the current
//                 coin
const SportsCard* SportsCard::copy() const
{
   const SportsCard* copied = new SportsCard(*this);
   return copied;
}
