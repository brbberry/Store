#include "SportsCard.h"

SportsCard::SportsCard(std::string key) :
   Collectible(key),
   player_(""),
   manufacturer_(""),
   year_(0),                
   grade_("")
{
}

SportsCard::~SportsCard()
{
}

const SportsCard* SportsCard::create(std::string toMakeFrom)
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

bool SportsCard::operator!=(const Comparable& right) const
{
   return !((*this) == right);
}

bool SportsCard::operator>(const Comparable& right) const
{
   const SportsCard& toCheck = static_cast<const SportsCard&>(right);

   bool greaterThan = true;
   if (static_cast<int>(player_.compare(toCheck.player_)) < 0) {
      return false;
   }
   if (year_ < toCheck.year_) {
      return false;
   }
   if (static_cast<int>(manufacturer_.compare(toCheck.manufacturer_)) < 0) {
      return false;
   }
   if (static_cast<int>(grade_.compare(toCheck.grade_)) < 0) {
      return false;
   }
   return greaterThan;
}

bool SportsCard::operator<(const Comparable& right) const
{
   const SportsCard& toCheck = static_cast<const SportsCard&>(right);
   bool lessThan = true;
   if (static_cast<int>(player_.compare(toCheck.player_)) > 0) {
      return false;
   }
   if (year_ < toCheck.year_) {
      return false;
   }
   if (static_cast<int>(manufacturer_.compare(toCheck.manufacturer_)) > 0) {
      return false;
   }
   if (static_cast<int>(grade_.compare(toCheck.grade_)) > 0) {
      return false;
   }

   return lessThan;
}

int SportsCard::hash() const
{
   return Collectible::hash();
}

void SportsCard::print() const
{
   std::cout << "Comic : " << year_ << ", " << grade_ << ", " + manufacturer_
      << ", " + player_;
}

int main() {
   return 0;
}