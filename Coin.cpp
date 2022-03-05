#include "Coin.h"

/*
   std::string type_; // the string type the coin is
   int year_;         // the year the coin originated from
   int grade_;        // the coins grade
*/




// ignoring count becuase we can let the item manager add this to the BST
// to increase the count when its found rather than it being a property
// of the coin.
Coin::Coin(std::string type) :
   Collectible(type),
   year_(0), 
   grade_(0),
   type_("")//,
   //count_(0)
{
}

Coin::~Coin()
{
}



const Coin* Coin::create(std::string toMakeFrom) const
{
   // makes a new coin becuase we dont want to edit the one produced 
   // by the factory

   Coin* dummy = new Coin();
   // assumes that year comes first
   
   dummy->year_ = std::stoi(Collectible::processConstruction(toMakeFrom));

   if (dummy->year_ < 1000 || dummy->year_ > 2022) {
      //throw error
   }

   // assumes grade comes second
   dummy->grade_ = std::stoi(Collectible::processConstruction(toMakeFrom));
   if (dummy->grade_ < 0) {
      //throw error
   }

   // assumes type comes last
   dummy->type_ = Collectible::processConstruction(toMakeFrom);

   return dummy;
}

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

bool Coin::operator!=(const Comparable& right) const
{
    return !((*this) == right);
}

// Checks if two Coins have a greater than relationship. Coins are weighted
// such that we first consider them by type, then by year, then by grade.
// The string type is compared then the following ints

bool Coin::operator>(const Comparable& right) const
{

   const Coin& toCheck = static_cast<const Coin&>(right);
   bool greaterThan = true;
   if (static_cast<int>(type_.compare(toCheck.type_)) < 0) {
      return false;
   }
   if (year_ < toCheck.year_) {
      return false;
   }
   if (grade_ < toCheck.grade_) {
      return false;
   }

   return greaterThan;
}

bool Coin::operator<(const Comparable& right) const
{

   const Coin& toCheck = static_cast<const Coin&>(right);
   bool lessThan = true;
   if (static_cast<int>(type_.compare(toCheck.type_)) > 0) {
      return false;
   }
   if (year_ > toCheck.year_) {
      return false;
   }
   if (grade_ > toCheck.grade_) {
      return false;
   }
   return lessThan;
}
 
int Coin::hash() const
{
   return Collectible::hash();
}

void Coin::print() const
{
   std::cout << "Coin : " << year_ << ", " << grade_ << ", " << type_;
}
/*
int main() {
   Collectible* testCoin = new Coin("M");
   const Collectible* created = testCoin->create(", 1913, 70, Liberty Nickel");

   std::cout << "Printing test coin" << std::endl;
   testCoin->print();
   std::cout << std::endl << "Printing created coin" << std::endl;
   created->print();

   std::cout << std::endl << "Printing test coin hash" << std::endl;
   std::cout << testCoin->hash() << std::endl;
   std::cout << std::endl << "Printing created coin" << std::endl;
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


   const Collectible* anotherCoinCreated = testCoin->create(", 2001, 65, Lincoln Cent");
   
   std::cout << "testing with an addition coin" << std::endl;
   std::cout << std::endl;
   std::cout << std::endl << "Printing test coin hash" << std::endl;
   std::cout << anotherCoinCreated->hash() << std::endl;
   std::cout << std::endl << "Printing created coin" << std::endl;
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
