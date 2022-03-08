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

//assumes valid grade title and publisher
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
   if (*this == right) {
      return false;
   }
   else {
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
}

bool Comic::operator<(const Comparable& right) const
{
   if (*this == right) {
      return false;
   }
   else {
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

const Comic* Comic::copy() const
{
   const Comic* copied = new Comic(*this);
   return copied;
}

/*
int main() {
   Collectible* testCoin = new Comic();
   const Collectible* created = testCoin->create(", 1938, Mint, Superman, DC");

   std::cout << "Printing test comic" << std::endl;
   testCoin->print();
   std::cout << std::endl << "Printing created comic" << std::endl;
   created->print();

   std::cout << std::endl << "Printing test comic hash" << std::endl;
   std::cout << testCoin->hash() << std::endl;
   std::cout << std::endl << "Printing created comic" << std::endl;
   std::cout << std::endl << created->hash() << std::endl;

   const Collectible* checkingBools = created;

   bool testEqualsY = created == checkingBools;
   // checking the bools
   std::cout << std::endl << "testing the bools == (true)" << std::endl;
   std::cout << std::endl << testEqualsY << std::endl;

   bool testEqualsN = created == testCoin;
   // checking the bools
   std::cout << std::endl << "testing the bools == (false)" << std::endl;
   std::cout << std::endl << testEqualsN << std::endl;

   bool testLEQN = created < checkingBools;
   // checking the bools
   std::cout << std::endl << "testing the bools < (false)" << std::endl;
   std::cout << std::endl << testLEQN << std::endl;

   bool testGEQN = created > checkingBools;
   // checking the bools
   std::cout << std::endl << "testing the bools > (false)" << std::endl;
   std::cout << std::endl << testGEQN << std::endl;


   const Collectible* anotherCoinCreated = testCoin->create(", 2010, Excellent, X-Men, Marvel");

   std::cout << "testing with an addition comic" << std::endl;
   std::cout << std::endl;
   std::cout << std::endl << "Printing test comic hash" << std::endl;
   std::cout << anotherCoinCreated->hash() << std::endl;
   std::cout << std::endl << "Printing created comic" << std::endl;
   std::cout << std::endl << created->hash() << std::endl;


   testEqualsY = created == anotherCoinCreated;
   // checking the bools
   std::cout << std::endl << "testing the bools ==" << std::endl;
   std::cout << std::endl << testEqualsY << std::endl;

   testEqualsN = created > anotherCoinCreated;
   // checking the bools
   std::cout << std::endl << "testing the bools > created first " << std::endl;
   std::cout << std::endl << testEqualsN << std::endl;

   testLEQN = created < anotherCoinCreated;
   // checking the bools
   std::cout << std::endl << "testing the bools < created first" << std::endl;
   std::cout << std::endl << testLEQN << std::endl;

   testGEQN = anotherCoinCreated > created;
   // checking the bools
   std::cout << std::endl << "testing the bools > another first " << std::endl;
   std::cout << std::endl << testGEQN << std::endl;




   delete testCoin;
   delete created;
   delete anotherCoinCreated;
   return 0;

}
*/
