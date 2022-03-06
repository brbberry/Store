#include "ItemsManager.h"


bool ItemsManager::CheckStore(std::string& key) const
{
   return false;
}

// assumes 
std::string ItemsManager::getItemType(std::string& instructions) const
{

   char collectibleTypeChar = instructions[0];
   std::string type = "";
   type.push_back(collectibleTypeChar);
   instructions.erase(0, 1);
   
   return type;
}

int ItemsManager::getQuantity(std::string& instructions) const
{
   // get rid of the leading ", "
   instructions.erase(0, 2);
   int numberStart = 0;
   int numberEnd = 0;
   bool validNumber = false;
   // if its valid mark it so
   while (std::isdigit(instructions[numberEnd])) {
      validNumber = true;
      numberEnd++;
   }

   if (!validNumber) {
      //throw an error
      return 0;
   }
   else {
      std::string stringCopies = instructions.substr(numberStart, numberEnd);
      int copies = std::stoi(stringCopies);
      instructions.erase(numberStart, numberEnd);
      return copies;
   }
}

ItemsManager::ItemsManager() :
   makeCollectibles_(CollectionFactory()),
   inventory_(std::vector<SearchTree*>())
{
   // really need to make a size variable
   for (int i = 0; i < 3; i++) {
      inventory_.push_back(new SearchTree());
   }

}

ItemsManager::~ItemsManager()
{
   for (int i = 0; i < 3; i++) {
      delete inventory_[i];
   }
}
/*
while we are not at the end of the file do
store first char as a string

use that string to get a dummy collectible from the factory
if nullptr is returned
throw an invalid errorand keep processing
else
try
call the collectibles create method on the remainder of
the string

catch
the exceptionand go to the next line of the file

if the collectible is in the store
increase the count
else
add call insert to add it to the inventory
*/
void ItemsManager::fillInventory(std::ifstream& inFile)
{
   std::string curItem = "";
   while (inFile.peek() != EOF) {

      std::getline(inFile, curItem);

      // we have the type
      std::string collectibleType = getItemType(curItem);
      // we know the first is the customer number

      //try
      // creates a itemShell (does not create memory)
      const Collectible* itemShell = makeCollectibles_.create(collectibleType);
      //catch

      // try
      int makeCopies = getQuantity(curItem);
      // catch

      // try
      const Collectible* itemToAdd = itemShell->create(curItem);
      // catch
      int numAdded = 0;

      const Comparable* comparableToAdd = static_cast<const Comparable*>(itemToAdd);
      while (numAdded < makeCopies) {

         if (itemToAdd->getID() == "M") {
            
            inventory_[0]->insert(comparableToAdd);
         }
         else if (itemToAdd->getID() == "C") {
            inventory_[1]->insert(comparableToAdd);
         }
         else if (itemToAdd->getID() == "S") {
            inventory_[2]->insert(comparableToAdd);
         }
         numAdded++;
      }
   }
}

bool ItemsManager::manageSelling(std::string collectible)
{

   // we have the type
   std::string collectibleType = getItemType(collectible);
   // we know the first is the customer number

   //try
   // creates a itemShell (does not create memory)
   const Collectible* itemShell = makeCollectibles_.create(collectibleType);
   //catch

   // try
   const Collectible* itemToSell = itemShell->create(collectibleType);
   // catch

   const Comparable* comparableToSell = static_cast<const Comparable*>(itemToSell);

   if (itemToSell->getID() == "M") {
      // if its already present free the memory as it isn't added
      if (!inventory_[0]->insert(comparableToSell)) {
         delete itemToSell;
      }
   }
   else if (itemToSell->getID() == "C") {
      // if its already present free the memory as it isn't added
      if (!inventory_[1]->insert(comparableToSell)) {
         delete itemToSell;
      }
   }
   else if (itemToSell->getID() == "S") {
      // if its already present free the memory as it isn't added
      if (!inventory_[2]->insert(comparableToSell)) {
         delete itemToSell;
      }
   }
   return true;
}

bool ItemsManager::manageBuying(std::string collectible)
{
   // we have the type
   std::string collectibleType = getItemType(collectible);
   // we know the first is the customer number

   //try
   // creates a itemShell (does not create memory)
   const Collectible* itemShell = makeCollectibles_.create(collectibleType);
   //catch

   // try
   const Collectible* itemToBuy = itemShell->create(collectibleType);
   // catch

   const Comparable* comparableToBuy = static_cast<const Comparable*>(itemToBuy);

   if (itemToBuy->getID() == "M") {

      inventory_[0]->remove(*comparableToBuy);
   }
   else if (itemToBuy->getID() == "C") {
      inventory_[1]->remove(*comparableToBuy);
   }
   else if (itemToBuy->getID() == "S") {
      inventory_[2]->remove(*comparableToBuy);
   }


   return false;
}

void ItemsManager::showInventory() const
{
   // make this FACTORY_SIZE
   for (int i = 0; i < 3; i++) {
      std::cout << *inventory_[i] << std::endl;
   }

}

int main() {
   ItemsManager* mgr = new ItemsManager();

   std::ifstream ifs("C:/Users/Trident/source/repos/StoreTesting/StoreTesting/Text1.txt");
   mgr->fillInventory(ifs);
   mgr->showInventory();
   delete mgr;
   return 0;
}