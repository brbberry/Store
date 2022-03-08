// Blake Berry
// 03/08/2022
// Homework 4
// This file is an implimentation for the ItemManager class. The ItemManager 
//  class has a collectible Factory and stores a sorted inventory seperated
// by collectible type. The ItemManager class is responsible for making sure
// an item to be acted on is valid or in the store. It is reponsible for
// filling in the stores initial inventory
//-----------------------------------------------------------------------------

#include "ItemsManager.h"


//------------------------ getItemType ------------------------------------
// Processes a line of instructions getting the item type from them and
// returning it
// Postconditions:  The item type must be 1 char and must be the first char
//                  in the instructions
std::string ItemsManager::getItemType(std::string& instructions) const
{

   char collectibleTypeChar = instructions[0];
   std::string type = "";
   type.push_back(collectibleTypeChar);
   instructions.erase(0, 1);
   
   return type;
}


//------------------------ getQuantity -------------------------------------
// Processes a line of input instructions extracting the quantity of a given
// item
// Preconditions : The instructions must lead with ", "
// Postconditions:  returns the quantity if valid and returns -1
//                  if invalid
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
      return -1;
   }
   else {
      std::string stringCopies = instructions.substr(numberStart, numberEnd);
      int copies = std::stoi(stringCopies);
      instructions.erase(numberStart, numberEnd);
      return copies;
   }
}


//------------------------ getItemShell ------------------------------------
// Takes a given string and checks the item factory for a collectible of 
// that type. 
// Postconditions: returns a pointer to a dummy item of the correct type
//                 otherwise an error is thrown
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


//------------------------ hashStoreInventory ------------------------------
// Creates an index in the invertory for a given item type
// Preconditions : Each collectible must have a unique item type
//                 the first char must between 'A' and 'Z' inclusive
// Postconditions:  returns a hash for an item type
int ItemsManager::hashStoreInventory(std::string itemType) const
{
   return itemType[0] - 'A';
}


//-------------------------- Default Constructor ---------------------------
// Creates an Item manager with a fully working factory and an empty 
// inventory
// Preconditions : The factory must be intialized with the items that are
//                 allowed in the collections store
// Postconditions: a new item manager is created
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


//-------------------------- Destructor -----------------------------------
// Frees any dynamic memory associated with the items manager class
// Preconditions : The factory must be capable to freeing its dynamic memory
//                   
//                 the items inventory must be capable of freeing its 
//                 dynamic memory
// 
// Postconditions: frees the memory associated with the items manager
ItemsManager::~ItemsManager()
{
   for (int i = 0; i < NUM_ITEM_TYPES; i++) {

      delete betterInventory_[i];
      betterInventory_[i] = nullptr;
   }
   delete[] betterInventory_;
}



//-------------------------- FillInventory ---------------------------------
// Fills the inventory from a file, Coins are index 0, Comics are index 2, 
// and SportsCards are index 3
// Preconditions : The factory must be initialized
// 
//                 The file must be formatted correctly
// 
// Postconditions: The ItemManagers inventory is filled, exceptions are 
//                 thrown if invalid data is attempted
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


//-------------------------- ManageBuying ---------------------------------
// Given the ID of an item them method handles the purchase of an item
// if the item is present its inventory count is decrimented appropriately
// Preconditions : the hashable object frees its own dynamically allocated
//                 memory
// 
//                 The factory must be initalized
// 
// Postconditions: An item is sold and the inventory is updated and true
//                 is returned. Throws an error if an invalid item is
//                 attempted to be purchased
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


//-------------------------- ManageSelling ---------------------------------
// Given the ID of an item them method handles the sale of an item
// if the item is present its inventory count is incrimented appropriately
// Preconditions : the hashable object frees its own dynamically allocated
//                 memory
// 
//                 The factory must be initalized
// 
// Postconditions: An item is sold and the inventory is updated and true
//                 is returned. Throws an error if an invalid item is
//                 attempted to be sold
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


//-------------------------- showInventory ---------------------------------
// Shows the inventory in a specified ordered, coins, comics, then 
// sports cards
// Preconditions : the search tree and comparables must be printable
// 
// Postconditions: prints the items to the console in the above order.
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
