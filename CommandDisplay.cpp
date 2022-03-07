#include "CommandDisplay.h"

CommandDisplay::CommandDisplay(std::string type) :
   Command(type)
{
}

CommandDisplay::~CommandDisplay()
{
}

int CommandDisplay::hash() const
{
    return 0;
}

void CommandDisplay::execute(TransactionManager*& tManager, ItemsManager*& iManager, CustomerManager*& cManager, std::string& command) const
{
   iManager->showInventory();
}
