#include "Comic.h"

// change id to type
Comic::Comic(std::string id) :
Collectible(id),
publisher_(""),
title_(""),
year_(0),
grade_("")
//count_(0)
{
}

Comic::~Comic()
{
}

const Comic* Comic::create(std::string toMakeFrom)
{
   Comic* dummy = new Comic();
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

   dummy->title_ = Collectible::processConstruction(toMakeFrom);

   dummy->publisher_ = Collectible::processConstruction(toMakeFrom);

   return dummy;
}

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

bool Comic::operator!=(const Comparable& right) const
{
   return !((*this) == right);
}

bool Comic::operator>(const Comparable& right) const
{
   const Comic& toCheck = static_cast<const Comic&>(right);
   bool greaterThan = true;
   if (static_cast<int>(publisher_.compare(toCheck.publisher_)) < 0) {
      return false;
   }
   if (static_cast<int>(title_.compare(toCheck.title_)) < 0) {
      return false;
   }
   if (year_ < toCheck.year_) {
      return false;
   }
   if (static_cast<int>(grade_.compare(toCheck.grade_)) < 0) {
      return false;
   }
   return greaterThan;
}

bool Comic::operator<(const Comparable& right) const
{
   const Comic& toCheck = static_cast<const Comic&>(right);
   bool lessThan = true;
   if (static_cast<int>(publisher_.compare(toCheck.publisher_)) > 0) {
      return false;
   }
   if (static_cast<int>(title_.compare(toCheck.title_)) > 0) {
      return false;
   }
   if (year_ > toCheck.year_) {
      return false;
   }
   if (static_cast<int>(grade_.compare(toCheck.grade_)) > 0) {
      return false;
   }
   return lessThan;
}

// possibly define hashable at the comparable level becuase 
int Comic::hash() const
{
   return Collectible::hash();
}

void Comic::print() const
{
   std::cout << "Comic : " << year_ << ", " << grade_ << ", " + publisher_
             << ", "  + title_;
}

