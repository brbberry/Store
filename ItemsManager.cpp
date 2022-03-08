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

int ItemsManager::hashStoreInventory(std::string itemType) const
{
   return itemType[0] - 'A';
}

ItemsManager::ItemsManager() :
   makeCollectibles_(CollectionFactory()),
   betterInventory_(nullptr)
{
   // really need to make a size variable
   betterInventory_ = new SearchTree * [NUM_ITEM_TYPES];
   for (int i = 0; i < NUM_ITEM_TYPES; i++) {
      betterInventory_[i] = new SearchTree();
   }
}

ItemsManager::~ItemsManager()
{
   for (int i = 0; i < NUM_ITEM_TYPES; i++) {

      delete betterInventory_[i];
      betterInventory_[i] = nullptr;
   }
   delete[] betterInventory_;
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

         // promised to be accurate in that we can create it so there is an index no checking needed
         int inventoryIndex = hashStoreInventory(itemToAdd->getID());
         if (numAdded == 0) {
            
            if (betterInventory_[inventoryIndex]->retrieve(*comparableToAdd) != nullptr) {
               alreadyInInventory = true;
            }
         }

         betterInventory_[inventoryIndex]->insert(comparableToAdd);

         numAdded++;
      }
      // insert will not add the memeory twice free it
      if (alreadyInInventory) {
         delete itemToAdd;
      }

      lineItem++;
   }
}

const Collectible* ItemsManager::manageBuying(std::string collectible)
{

   // we have the type
   std::string collectibleType = getItemType(collectible);
   // we know the first is the customer number


   const Collectible* itemShell = makeCollectibles_.create(collectibleType);
   if (itemShell == nullptr) {
      throw CollectiblesStoreError("Cannot Process Purchase, Item cannot be Bought");
   }

   // this statement will throw bc create throws
   const Collectible* itemToBuy = itemShell->create(collectible);

   const Comparable* comparableToBuy = static_cast<const Comparable*>(itemToBuy);

   // assured to be valid
   int inventoryIndex = hashStoreInventory(itemToBuy->getID());
   if (!betterInventory_[inventoryIndex]->insert(comparableToBuy)) {
      const Comparable* actedOn = betterInventory_[inventoryIndex]->retrieve(*comparableToBuy);
      delete itemToBuy;
      return static_cast<const Collectible*>(actedOn);
   }
   else {
      return itemToBuy;
   }
   
}

const Collectible* ItemsManager::manageSelling(std::string collectible)
{
   std::string origin = collectible;
   std::string err1 = "Cannot Process Sale";
   // we have the type
   std::string collectibleType = getItemType(collectible);
   // we know the first is the customer number

   //try
   // creates a itemShell (does not create memory)
   const Collectible* itemShell = makeCollectibles_.create(collectibleType);
   //catch
   if (itemShell == nullptr) {

      throw CollectiblesStoreError(err1+" Invalid Item Type " + collectible);
   }
 
   // throws its own errors makes new memory
   const Collectible* itemToBuy = itemShell->create(collectible);

   const Comparable* comparableToBuy = static_cast<const Comparable*>(itemToBuy);

   int inventoryIndex = hashStoreInventory(itemToBuy->getID());
   // if it fails to remove an item free the memory and report back
   if (!betterInventory_[inventoryIndex]->remove(*comparableToBuy)) {
      delete itemToBuy;
      throw CollectiblesStoreError(origin +" is out of stock cannot be sold\n");
   }
   // if the item is removed successfully then go ahead and return it
   else {
      const Comparable* actedOn = betterInventory_[inventoryIndex]->retrieve(*comparableToBuy);
      delete itemToBuy;
      return static_cast<const Collectible*>(actedOn);
   }

}

void ItemsManager::showInventory() const
{
   std::vector<Collectible*> printInOrder;
   Coin first;
   Comic second;
   SportsCard third;
   printInOrder.push_back(static_cast<Collectible*>(&first));
   printInOrder.push_back(static_cast<Collectible*>(&second));
   printInOrder.push_back(static_cast<Collectible*>(&third));

   int printInOrderSize = printInOrder.size();

   for (int i = 0; i < printInOrderSize; i++) {
      int index = hashStoreInventory(printInOrder[i]->getID());
      std::cout << *betterInventory_[index];
   }
   std::cout << "\n" << std::endl;
}
