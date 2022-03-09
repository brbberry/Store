// Blake Berry
// 03/08/2022
// Homework 4
// This file is an implimentation for the Collectible store class. The
// CollectibleStore class inherets from the store abstract base class.
// The CollectibleStore class is constructed from two files containing a 
// list of customers and a list of collectible items that the store has along
// with their inventory. The CollectibleStore class will run the store given
// a commands file
//------------------------------------------------------------------------------

#include "CollectibleStore.h"


//------------------------ getCommandType ---------------------------------
// takes a string and abstracts the command type 
// PreConditions : The command type must be one char, the first char in the
//                 string. Assumed to be 'A' - 'Z'
// Postconditions: returns a string for the command type and modifies the 
//                 instructions string removing this char
std::string CollectibleStore::getCommandType(std::string& instructions) const
{
   std::string command = "";
   char commandType = instructions[0];
   command.push_back(commandType);
   instructions.erase(0, 1);
   return command;
}

void CollectibleStore::initalizeItemsManager(std::ifstream& readInventory)
{
   iManager_->fillInventory(readInventory);
}


//----------------- initalizeTransactionManager ----------------------------
// Creates the transaction manager 
// PreConditions : Needs to be initialized before the store is ran
// Postconditions: The transaction manager is created
void CollectibleStore::initalizeTransactionManager()
{
}


//-------------------- initalizeCustomerManager ----------------------------
// Creates the customer manager, initalizing the customer list from a file
// PreConditions : Needs to be initialized before the store is ran
//                 The file is assumed to be formatted but not necessarily
//                 valid
// Postconditions: The customer manager is created along with the stores
//                 customerlist
void CollectibleStore::initalizeCustomerManager(std::ifstream& readCustomers)
{
   cManager_->fillCustomerLog(readCustomers);
}


//------------------------ hashCommands ---------------------------------
// takes a string command and generates a hash based off that command
// PreConditions : The command type must be one char, the first char in the
//                 string. Assumed valid if 'A' - 'Z'
// Postconditions: returns an integer hash 'Char' - 'A' for the given
//                 command
int CollectibleStore::hashCommands(std::string key) const
{
    return key[0] - 'A';
}


//-------------------------- Constructor -----------------------------------
// Creates a store with an empty managers. The command factory is filled 
// manually based upon the hash of that command. 
// Preconditions : The Manager classes and factory classes must be 
//                 implimented
// 
//                 There are at most 26 commands with no commands sharing
//                 the same key
// 
//                 Assumes no collisions
// Postconditions: A store with an inventory, customer list, and empty 
//                 transaction log is created
CollectibleStore::CollectibleStore()
{
   iManager_ = new ItemsManager();
   tManager_ = new TransactionManager();
   cManager_ = new CustomerManager();

   generateCommand_ = new Command * [NUM_COMMANDS];
   for (int i = 0; i < NUM_COMMANDS; i++) {
      generateCommand_[i] = nullptr;
   }

   std::vector<Command*> toProcess;

   Command* buy = new CommandBuy();
   Command* sell = new CommandSell();
   Command* display = new CommandDisplay();
   Command* history = new CommandHistory();
   Command* customer = new CommandCustomer();

   toProcess.push_back(buy);
   toProcess.push_back(sell);
   toProcess.push_back(display);
   toProcess.push_back(history);
   toProcess.push_back(customer);

   int toProcessSize = toProcess.size();

   for (int i = 0; i < toProcessSize; i++) {

      int hash = hashCommands(toProcess[i]->getID());
      if (hash >= 0 && hash < NUM_COMMANDS) {
         generateCommand_[hash] = toProcess[i];
      }
   }
}


//-------------------------- destructor -----------------------------------
// Frees the memory associated with the store
// Preconditions : The managers desructors free their associated memory
// Postconditions: The store is cleared of all the dynamic memory that is 
//                 associated
CollectibleStore::~CollectibleStore()
{
   delete tManager_;
   delete iManager_;
   delete cManager_;

   // clearing out the command factory
   for (int i = 0; i < NUM_COMMANDS; i++) {
      if (generateCommand_[i] != nullptr) {
         delete generateCommand_[i];
         generateCommand_[i] = nullptr;
      }
   }
   delete[] generateCommand_;
}


//------------------------ runStore ----------------------------------------
// Operates the store, processes store commands from a file, and displays to
// the console.
// PreConditions : The store managers must be initialized
//                 The infile must be formatted correctly but not 
//                 necessarily valid
// Postconditions: The store managers are modified by the commands file
//                 and the store operations that can display to the console
//                 display to the console.
void CollectibleStore::runStore(std::ifstream& readCommands)
{
   std::string err1 = "Undefined Command Type";
   std::string curCommand = "";
   while (readCommands.peek() != EOF) {

      std::getline(readCommands, curCommand);

      // assumes command type is first
      std::string commandType = getCommandType(curCommand);

      // hash the command
      int commandIndex = hashCommands(commandType);
      if (commandIndex < 0 || commandIndex >= NUM_COMMANDS) {
         std::cout << err1 + " '" + commandType + "'\n" << std::endl;
      }
      else {

         Command* toDo = generateCommand_[commandIndex];
         if (toDo == nullptr) {
            std::cout << err1 + " '" + commandType + "'\n" << std::endl;
         }
         else {
            try {
               toDo->execute(tManager_, iManager_, cManager_, curCommand);
            }
            catch (CollectiblesStoreError err) {
               std::cout << err.what() << std::endl;
               continue;
            }
         }
      }
   }
}


//------------------------ fillStoreInventory ---------------------------
// Fills the store with items and outputs any errors to the console
// PreConditions : The input file must be formatted correctly even if the
//                 data is invalid
// Postconditions: The store is filled with items and any errors are 
//                 output to the console
void CollectibleStore::fillStoreInventory(std::ifstream& readInventory)
{
   initalizeItemsManager(readInventory);
}


//-------------------- fillStoreCustomers ---------------------------------
// Fills the store with known customers and outputs any errors to the 
// console
// PreConditions : The input file must be formatted correctly even if the
//                 data is invalid
// Postconditions: The store is filled with a customer list and any errors
//  are output to the console
void CollectibleStore::fillStoreCustomers(std::ifstream& readCustomers)
{
   initalizeCustomerManager(readCustomers);
}

int main() {

   std::ifstream custs("C:/Users/Trident/source/repos/StoreTesting/StoreTesting/Text.txt");
   std::ifstream items("C:/Users/Trident/source/repos/StoreTesting/StoreTesting/Text1.txt");
   std::ifstream commands("C:/Users/Trident/source/repos/StoreTesting/StoreTesting/Text2.txt");

   CollectibleStore* store = new CollectibleStore();
   store->fillStoreInventory(items);
   store->fillStoreCustomers(custs);
   store->runStore(commands);

   delete store;
   return 0;
}