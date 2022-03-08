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
      // invalid inventory
      return 0;
   }
   else {
      std::string stringCopies = instructions.substr(numberStart, numberEnd);
      int copies = std::stoi(stringCopies);
      instructions.erase(numberStart, numberEnd);
      return copies;
   }
}

const Collectible* ItemsManager::getItemShell(std::string& type) const
{

   const Collectible* itemShell = makeCollectibles_.create(type);

   if (itemShell == nullptr) {
      throw CollectiblesStoreError("Invalid Item Type");
   }
   else {
      return itemShell;
   }
}

int ItemsManager::getInventoryAmount(std::string& item) const
{
   int number = getQuantity(item);
   if (number <= 0) {
      throw CollectiblesStoreError("Invalid Item Quantity");
   }
   else {
      return number;
   }
}

ItemsManager::ItemsManager() :
   makeCollectibles_(CollectionFactory()),
   inventory_(std::vector<SearchTree*>())
{
   // really need to make a size variable
   for (int i = 0; i < NUM_ITEM_TYPES; i++) {
      inventory_.push_back(new SearchTree());
   }

}

ItemsManager::~ItemsManager()
{
   for (int i = 0; i < NUM_ITEM_TYPES; i++) {
      delete inventory_[i];
   }
}


void ItemsManager::fillInventory(std::ifstream& inFile)
{
   std::string curItem = "";
   bool itemError = false;
   int lineItem = 1;
   while (inFile.peek() != EOF) {

      std::getline(inFile, curItem);

      // we have the type
      std::string collectibleType = getItemType(curItem);
      // we know the first is the customer number

      //try
      // creates a itemShell (does not create memory)
      const Collectible* itemShell = nullptr;
      try {
         itemShell = getItemShell(collectibleType);
      }
      catch (CollectiblesStoreError err) {
         std::cout << "Inventory Line item " << lineItem << " "
                   << err.what() << std::endl;
         lineItem++;
         continue;
      }
      
      int inventoryAmount = 0;
      try {
         inventoryAmount = getInventoryAmount(curItem);
      }
      catch (CollectiblesStoreError err) {
         std::cout << "Inventory Line item " << lineItem << " "
            << err.what() << std::endl;
         lineItem++;
         continue;
      }

      const Collectible* itemToAdd = nullptr;
      try {
         itemToAdd = itemShell->create(curItem);
      }
      catch (CollectiblesStoreError err) {
         delete itemToAdd;
         std::cout << "Inventory Line item " << lineItem << " "
            << err.what() << std::endl;
         lineItem++;
         continue;
      }
      
      int numAdded = 0;

      const Comparable* comparableToAdd = static_cast<const Comparable*>(itemToAdd);

      bool alreadyInInventory = false;

      while (numAdded < inventoryAmount) {

         if (itemToAdd->getID() == "M") {
            if (numAdded == 0) {
               if (inventory_[0]->retrieve(*comparableToAdd) != nullptr) {
                  alreadyInInventory = true;
               }
            }

            inventory_[0]->insert(comparableToAdd);

         }
         else if (itemToAdd->getID() == "C") {
            if (numAdded == 0) {
               if (inventory_[1]->retrieve(*comparableToAdd) != nullptr) {
                  alreadyInInventory = true;
               }
            }

            inventory_[1]->insert(comparableToAdd);
         }
         else if (itemToAdd->getID() == "S") {
            if (numAdded == 0) {
               if (inventory_[2]->retrieve(*comparableToAdd) != nullptr) {
                  alreadyInInventory = true;
               }
            }

            inventory_[2]->insert(comparableToAdd);
         }
         numAdded++;
      }
      // insert will not add the memeory twice free it
      if (alreadyInInventory) {
         delete itemToAdd;
      }

      lineItem++;
   }
}

const Collectible* ItemsManager::manageSelling(std::string collectible)
{

   // we have the type
   std::string collectibleType = getItemType(collectible);
   // we know the first is the customer number


   const Collectible* itemShell = makeCollectibles_.create(collectibleType);
   if (itemShell == nullptr) {
      throw CollectiblesStoreError("Cannot Process Sale, Item cannot be Sold");
   }

   // this statement will throw bc create throws
   const Collectible* itemToSell = itemShell->create(collectible);

   const Comparable* comparableToSell = static_cast<const Comparable*>(itemToSell);

   if (itemToSell->getID() == "M") {
      // if its already present free the memory as it isn't added
      // keeps the memory owned by the items manager -- hence retrieve call
      if (!inventory_[0]->insert(comparableToSell)) {
         const Comparable* actedOn = inventory_[0]->retrieve(*comparableToSell);
         delete itemToSell;
         return static_cast<const Collectible*>(actedOn);
      }
      else {
         /*
         * 
         * GETTING RID OF THIS BC Same pointer would be in the table
         const Comparable* actedOn = inventory_[0]->retrieve(*comparableToSell);
         return static_cast<const Collectible*>(actedOn);
         */
         return itemToSell;
      }
   }
   else if (itemToSell->getID() == "C") {
      // if its already present free the memory as it isn't added
      if (!inventory_[1]->insert(comparableToSell)) {
         const Comparable* actedOn = inventory_[1]->retrieve(*comparableToSell);
         delete itemToSell;
         return static_cast<const Collectible*>(actedOn);
      }
      else {
         /*
         const Comparable* actedOn = inventory_[1]->retrieve(*comparableToSell);
         return static_cast<const Collectible*>(actedOn);
         */
         return itemToSell;
      }
   }
   else if (itemToSell->getID() == "S") {
      // if its already present free the memory as it isn't added
      if (!inventory_[2]->insert(comparableToSell)) {
         const Comparable* actedOn = inventory_[2]->retrieve(*comparableToSell);
         delete itemToSell;
         return static_cast<const Collectible*>(actedOn);
      }
      else {
         /*
         const Comparable* actedOn = inventory_[2]->retrieve(*comparableToSell);
         return static_cast<const Collectible*>(actedOn);
         */
         return itemToSell;
      }
   }

   return nullptr;
}

const Collectible* ItemsManager::manageBuying(std::string collectible)
{
   std::string err1 = "Cannot Process Purchase";
   // we have the type
   std::string collectibleType = getItemType(collectible);
   // we know the first is the customer number

   //try
   // creates a itemShell (does not create memory)
   const Collectible* itemShell = makeCollectibles_.create(collectibleType);
   //catch
   if (itemShell == nullptr) {

      throw CollectiblesStoreError(err1+" Invalid Item Type");
   }
 
   // throws its own errors
   const Collectible* itemToBuy = itemShell->create(collectible);

   const Comparable* comparableToBuy = static_cast<const Comparable*>(itemToBuy);

   if (itemToBuy->getID() == "M") {
      // if false throw 
      const Comparable* actedOn = inventory_[0]->retrieve(*comparableToBuy);
      if (actedOn == nullptr) {
         throw CollectiblesStoreError(err1 + " Item Not Currently in Store");
      }
      inventory_[0]->remove(*comparableToBuy);
      return static_cast<const Collectible*>(actedOn);
   }
   else if (itemToBuy->getID() == "C") {
      
      const Comparable* actedOn = inventory_[1]->retrieve(*comparableToBuy);
      if (actedOn == nullptr) {
         throw CollectiblesStoreError(err1 + " Item Not Currently in Store");
      }
      inventory_[1]->remove(*comparableToBuy);
      return static_cast<const Collectible*>(actedOn);
   }
   else if (itemToBuy->getID() == "S") {
      
      const Comparable* actedOn = inventory_[2]->retrieve(*comparableToBuy);

      if (actedOn == nullptr) {
         throw CollectiblesStoreError(err1 + " Item Not Currently in Store");
      }

      inventory_[2]->remove(*comparableToBuy);
      return static_cast<const Collectible*>(actedOn);
   }

   return nullptr;
}

void ItemsManager::showInventory() const
{

   for (int i = 0; i < NUM_ITEM_TYPES; i++) {
      if (!inventory_[i]->isEmpty()) {
         std::cout << *inventory_[i] << std::endl;
      }
   }
}

/*
int main() {
   ItemsManager* mgr = new ItemsManager();

   std::ifstream ifs("C:/Users/Trident/source/repos/StoreTesting/StoreTesting/Text1.txt");
   mgr->fillInventory(ifs);
   mgr->showInventory();
   delete mgr;
   return 0;
}
*/