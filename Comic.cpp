// Blake Berry
// 03/08/2022
// Homework 4
// This file is an implimentation for the Comic class. The Comic class inherted
// from the collectible interface. The Comic class represents an item that can
// exist at a collectible store
//-----------------------------------------------------------------------------

#include "Comic.h"


//-------------------------- Constructor -----------------------------------
// Creates a completely empty comic with empty fields
// Postconditions: an empty comic is created
Comic::Comic(std::string id) :
Collectible(id),
publisher_(""),
title_(""),
year_(0),
grade_("")
{
}


//-------------------------- destructor -----------------------------------
// Frees any dynamic memory associated with the Comic
// Postconditions: The comic is freed of any dynamic memory
Comic::~Comic()
{
}


//-------------------------- Create --------------------------------------
// Parses a given string and created a comic from a given string returning 
// itself
// PreConditions : The comic data must be formatted correctly in the string
// Postconditions: returns a constant pointer to the created Comic
//                 throws an exception if any of the information is invalid
const Comic* Comic::create(std::string toMakeFrom) const
{
   Comic* dummy = new Comic();
   // assumes that year comes first

   dummy->year_ = std::stoi(Collectible::processConstruction(toMakeFrom));

   if (dummy->year_ < 1000 || dummy->year_ > 2022) {
      throw CollectiblesStoreError("Invalid Comic Year");
   }

   dummy->grade_ = Collectible::processConstruction(toMakeFrom);

   dummy->title_ = Collectible::processConstruction(toMakeFrom);

   dummy->publisher_ = Collectible::processConstruction(toMakeFrom);

   return dummy;
}


//-------------------------- operator== ------------------------------------
// Checks if two Comics are equivilent. Equivilance is defined as each 
// Comic having the same publisher, title year and grade.
// Postconditions: Returns true if both Comics are equivilent
//                 Returns false if the Comics are not equivilent.
bool Comic::operator==(const Comparable& right) const
{
   const Comic& toCheck = static_cast<const Comic&>(right);
   bool equiv = true;
   if (publisher_ != toCheck.publisher_) {
      return false;
   }
   if (title_ != toCheck.title_) {
      return false;
   }
   if (year_ != toCheck.year_) {
      return false;
   }
   if (grade_ != toCheck.grade_) {
      return false;
   }
   return equiv;
}


//-------------------------- operator!= ------------------------------------
// Checks if two Comics are not  equivilent. Equivilance is defined as each 
// Comic having the same publisher, title year and grade.
// Preconditions : The right hand side comparable must be defined
// Postconditions: Returns true if both Comics are not equivilent
//                 Returns false if the Comics are equivilent.
bool Comic::operator!=(const Comparable& right) const
{
   return !((*this) == right);
}


//-------------------------- operator> -------------------------------------
// Checks if two Comics have a greater than relationship. Comics are 
// weighted such that we first consider them by publisher, then by title,
// then by year, then by grade. The fields are compared using defined >
// Postconditions: Returns true if the right hand side comic is smaller
//                 than the left hand side. Otherwise, false is returned
bool Comic::operator>(const Comparable& right) const
{

   const Comic& toCheck = static_cast<const Comic&>(right);

   if (publisher_ > toCheck.publisher_) {
      return true;
   }
   else if (publisher_ == toCheck.publisher_) {
      if (title_ > toCheck.title_) {
         return true;
      }
      else if (title_ == toCheck.title_) {
         if (year_ > toCheck.year_) {
            return true;
         }
         else if (year_ == toCheck.year_) {
            if (grade_ > toCheck.grade_) {
               return true;
            }
         }
      }
   }

   return false;
}


//-------------------------- operator< --------------------------------------
// Checks if two Comics have a less than relationship. Comics are 
// weighted such that we first consider them by publisher, then by title,
// then by year, then by grade. The fields are compared using defined <
// Postconditions: Returns true if the right hand side comic is larger
//                 than the left hand side. Otherwise, false is returned
bool Comic::operator<(const Comparable& right) const
{

   const Comic& toCheck = static_cast<const Comic&>(right);
   if (publisher_ < toCheck.publisher_) {
      return true;
   }
   else if (publisher_ == toCheck.publisher_) {
      if (title_ < toCheck.title_) {
         return true;
      }
      else if (title_ == toCheck.title_) {
         if (year_ < toCheck.year_) {
            return true;
         }
         else if (year_ == toCheck.year_) {
            if (grade_ < toCheck.grade_) {
               return true;
            }
         }
      }
   }

   return false;
}


//-------------------------- print --------------------------------------
// Prints the comics publisher, title, year, and grade on one line
// Postconditions: prints to the console a representation of the Comic
void Comic::print() const
{
   std::cout << "Comic : " << year_ << ", " << grade_ << ", " + publisher_
             << ", "  + title_;
}


//-------------------------- copy ------------------------------------------
// creates a deep copy of the current comic and returns a non-modifyable
// pointer to it
// preconditions : The caller must means to deallocate the memory
//                 associated
// Postconditions: returns a constant pointer deep copy of the current
//                 comic
const Comic* Comic::copy() const
{
   const Comic* copied = new Comic(*this);
   return copied;
}
