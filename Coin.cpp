// Blake Berry
// 03/08/2022
// Homework 4
// This file is an implimentation for the Coin class. The Coin class inherted
// from the collectible interface. The Coin class represents an item that can
// exist at a collectible store
//-----------------------------------------------------------------------------

#include "Coin.h"


//-------------------------- Constructor -----------------------------------
// Creates a completely empty coin with empty fields
// Postconditions: an empty coin is created
Coin::Coin(std::string type) :
   Collectible(type),
   year_(0), 
   grade_(0),
   type_("")
{
}


//-------------------------- destructor -----------------------------------
// Frees any dynamic memory associated with the Coin
// Postconditions: The coin is freed of any dynamic memory
Coin::~Coin()
{
}


//-------------------------- Create --------------------------------------
// Parses a given string and created a coin from a given string returning 
// itself
// PreConditions : The coin data must be formatted correctly in the string
// Postconditions: returns a constant pointer to the created Coin
//                 throws an exception if any of the information is invalid
const Coin* Coin::create(std::string toMakeFrom) const
{

   // creates a new coin
   Coin* dummy = new Coin();

   // assumes that year is first
   dummy->year_ = std::stoi(Collectible::processConstruction(toMakeFrom));

   // validates year
   if (dummy->year_ < 1000 || dummy->year_ > 2022) {
      throw CollectiblesStoreError("Invalid Coin Year");
   }

   // assumes grade is second
   dummy->grade_ = std::stoi(Collectible::processConstruction(toMakeFrom));
   if (dummy->grade_ < 0) {
      throw CollectiblesStoreError("Invalid Coin Grade");
   }

   // assumes is third
   dummy->type_ = Collectible::processConstruction(toMakeFrom);

   return dummy;
}


//-------------------------- operator== --------------------------------------
// Checks if two Coins are equivilent. Equivilance is defined as each 
// Coin having the sametype year and grade
// Postconditions: Returns true if both Coins are equivilent
//                 Returns false if the Coins are not equivilent.
bool Coin::operator==(const Comparable& right) const
{

   const Coin& toCheck = static_cast<const Coin&>(right);
   bool equiv = true;
   if (year_ != toCheck.year_) {
      return false;
   }
   if (grade_ != toCheck.grade_) {
      return false;
   }
   if(type_ != toCheck.type_){
      return false;
   }

   return equiv;
}


//-------------------------- operator!= --------------------------------------
// Checks if two Coins are not equivilent. Equivilance is defined as each 
// Coin having the sametype year and grade
// Postconditions: Returns true if both Coins are not  equivilent
//                 Returns false if the Coins are equivilent.
bool Coin::operator!=(const Comparable& right) const
{
    return !((*this) == right);
}


//-------------------------- operator> --------------------------------------
// Checks if two Coins have a greater than relationship. Coins are weighted
// such that we first consider them by type, then by year, then by grade.
// The string type is compared then the following ints
// Postconditions: Returns true if the right hand side coin is smaller
//                 than the left hand side. Otherwise, false is returned
bool Coin::operator>(const Comparable& right) const
{
   if (*this == right) {
      return false;
   }
   else {
      const Coin& toCheck = static_cast<const Coin&>(right);
      bool greaterThan = true;

      // uses string compare
      if (type_ < toCheck.type_) {
         return false;
      }
      // a lesser year is greater
      if (year_ < toCheck.year_) {
         return false;
      }
      // a higher grade is greater
      if (grade_ > toCheck.grade_) {
         return false;
      }

      return greaterThan;
   }
}


//-------------------------- operator< --------------------------------------
// Checks if two Coins have a less than relationship. Coins are weighted
// such that we first consider them by type, then by year, then by grade.
// The string type is compared then the following ints
// Postconditions: Returns false if the right hand side Coin is smaller
//                 than the left hand side. Otherwise, true is returned
bool Coin::operator<(const Comparable& right) const
{
   if (*this == right) {
      return false;
   }
   else {
      const Coin& toCheck = static_cast<const Coin&>(right);
      bool lessThan = true;

      // uses string compare
      if (type_ > toCheck.type_) {
         return false;
      }
      // a smaller year is greater
      if (year_ < toCheck.year_) {
         return false;
      }
      // a higher grade is greater
      if (grade_ > toCheck.grade_) {
         return false;
      }
      return lessThan;
   }
}
 

//-------------------------- print --------------------------------------
// Prints the coins type year and grade on one line
// Postconditions: prints to the console a representation of the Coin
void Coin::print() const
{
   std::cout << "Coin : " << year_ << ", " << grade_ << ", " << type_;
}


//-------------------------- copy ------------------------------------------
// creates a deep copy of the current coin and returns a non-modifyable
// pointer to it
// preconditions : The caller must means to deallocate the memory
//                 associated
// Postconditions: returns a constant pointer deep copy of the current
//                 coin
const Coin* Coin::copy() const
{
   // default copy as coin contains only primatives
   const Coin* toCopy = new Coin(*this);
   return toCopy;
}
