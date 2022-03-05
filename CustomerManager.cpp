#include "CustomerManager.h"

bool CustomerManager::checkCustomerLog(const HashableObject& toGet) const
{
   int position = toGet.hash();

   if (position < 0 || position >= numCustomers_) {
      return false;
   }
   else if (customerLog_[position] == nullptr) {
      return false;
   }
   else {
      return true;
   }
}

std::string CustomerManager::processCustomer(std::string& curLine) const
{
   int startPosition = 0;
   int endPosition = 0;

   if (curLine == "" || startPosition > curLine.length()) {
      return "";
   }

   // format {, data} position 2 is the first char of the data
   while (endPosition < curLine.length() &&
      curLine[endPosition] != ',') {

      endPosition++;
   }

   std::string data;

   if (endPosition == curLine.length()) {
      data = curLine.substr(startPosition, endPosition);
      // to handle deletion apprpraiately
      endPosition = curLine.length();
   }
   else {
      data = curLine.substr(startPosition, endPosition);
      // to handle deletion apprpraiately
      endPosition += 2;
   }

   // update the instructions to get the next piece of data
   curLine.erase(0, endPosition);
   return data;
}

int CustomerManager::hashCustomer(std::string customerNumber) const
{
   return std::stoi(customerNumber);
}

bool CustomerManager::validCustomerHash(int customerIndex) const
{
   return (customerIndex >= 0) && (customerIndex < numCustomers_);
}


// possibly include 1000 as a comment somewhere
CustomerManager::CustomerManager(int numCustomers) :
   customerLog_(nullptr),
   numCustomers_(numCustomers)
{
   // ensure valid ?
   if (numCustomers <= 0) {
      numCustomers = 1000;
   }

   customerLog_ = new HashableObject * [numCustomers_];

   for (int i = 0; i < numCustomers_; i++) {
      customerLog_[i] = nullptr;
   }
}

CustomerManager::~CustomerManager()
{
   for (int i = 0; i < numCustomers_; i++) {
      delete customerLog_[i];
      customerLog_[i] = nullptr;
   }
   delete[] customerLog_;
}

void CustomerManager::fillCustomerLog(std::ifstream& readFrom)
{
   std::string curCust = "";
   while (readFrom.peek() != EOF) {
      
      std::getline(readFrom, curCust);
      std::string customerNumberString = processCustomer(curCust);
      // we know the first is the customer number
      int customerNumber = std::stoi(customerNumberString);
      int custIndex = hashCustomer(customerNumberString);

      if (customerLog_[custIndex] == nullptr) {
         std::string custName = processCustomer(curCust);
         HashableObject* newCustomer = new Customer(customerNumber, custName);
         customerLog_[custIndex] = newCustomer;
      }
      else {
         // throw an error
      }
   }
}

const Customer* CustomerManager::findCustomer(std::string ID)
{

   int customerIndex = hashCustomer(ID);

   if (validCustomerHash(customerIndex)) {
      
      if (customerLog_[customerIndex] == nullptr) {
         return nullptr;
      }
      else {
         return static_cast<const Customer*>(customerLog_[customerIndex]);
      }
   }
}
/*
int main() {
   
   CustomerManager* manager = new CustomerManager();
   std::ifstream ifs("C:/Users/Trident/source/repos/StoreTesting/StoreTesting/Text.txt");

   manager->fillCustomerLog(ifs);
   const Customer* found = manager->findCustomer("001");
   std::cout << found->getName();

   delete manager;
   return 0;

}
*/