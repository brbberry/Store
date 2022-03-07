#include "CommandHistory.h"

CommandHistory::CommandHistory(std::string type) :
   Command(type)
{
}

CommandHistory::~CommandHistory()
{
}

int CommandHistory::hash() const
{
    return 0;
}

void CommandHistory::execute(TransactionManager*& tManager, ItemsManager*& iManager, CustomerManager*& cManager, std::string& command) const
{
   tManager->displayTransactionHistory();
}
