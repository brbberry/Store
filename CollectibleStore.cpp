#include "CollectibleStore.h"

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

void CollectibleStore::initalizeTransactionManager()
{
}

void CollectibleStore::initalizeCustomerManager(std::ifstream& readCustomers)
{
   cManager_->fillCustomerLog(readCustomers);
}

int CollectibleStore::hashCommands(std::string key) const
{
    return key[0] - 'A';
}

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

   for (int i = 0; i < toProcess.size(); i++) {

      int hash = hashCommands(toProcess[i]->getID());
      if (hash >= 0 && hash < NUM_COMMANDS) {
         if (generateCommand_[hash] == nullptr) {
            generateCommand_[hash] = toProcess[i];
         }
         else {
            //throw error maybe get rid of
         }
      }
   }
}


CollectibleStore::~CollectibleStore()
{
   delete iManager_;
   delete tManager_;
   delete cManager_;

   for (int i = 0; i < NUM_COMMANDS; i++) {
      if (generateCommand_[i] != nullptr) {
         delete generateCommand_[i];
         generateCommand_[i] = nullptr;
      }
   }
   delete[] generateCommand_;
}

void CollectibleStore::runStore(std::ifstream& readCommands)
{

   std::string curCommand = "";
   while (readCommands.peek() != EOF) {

      std::getline(readCommands, curCommand);

      // we have the type
      std::string commandType = getCommandType(curCommand);
      // we know the first is the customer number

      //try
      int commandIndex = hashCommands(commandType);
      if (commandIndex < 0 || commandIndex >= NUM_COMMANDS) {
         //throw
      }
      else {
         // try
         Command* toDo = generateCommand_[commandIndex];
         if (toDo == nullptr) {
            //throw
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


void CollectibleStore::fillStoreInventory(std::ifstream& readInventory)
{
   initalizeItemsManager(readInventory);
}

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