#include "CustomerManager.h"

bool CustomerManager::checkCustomerLog(const HashableObject& toGet) const
{
    return false;
}

// possibly include 1000 as a comment somewhere
CustomerManager::CustomerManager() :
   customerLog_(HashTable(1000))
{
}

CustomerManager::~CustomerManager()
{
}

void CustomerManager::fillCustomerLog(const std::ifstream& readFrom)
{
}

const Customer* CustomerManager::findCustomer(std::string ID)
{
    return nullptr;
}
