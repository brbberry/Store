// Blake Berry
// 03/08/2022
// Homework 4
// This file is an implimentation for the CustomerManager class. The 
//  Customermanager  class stores a hashtable of customers for quick look up 
// based upon a customers customer number. This class is responsible for 
// checking for valid customers and returning customer information to those 
// that request it. It  is also repsonsible for filling in the stores original 
// customer list
//-----------------------------------------------------------------------------

#include "CustomerManager.h"


//------------------- validCustomerNumber ----------------------------------
// Checks if a string represtation of an item is valid
// Postconditions: returns true if the customer number is valid and returns
//                 false otherwise
bool CustomerManager::validCustomerNumber(std::string custNum) const
{
   std::string err = "Invalid Customer Number ";
   int length = custNum.size();

   if (length != 3) {
      throw CollectiblesStoreError(err + custNum + "\n");
   }
   else {
      for (int i = 0; i < length; i++) {
         if (!std::isdigit(custNum[i])) {
            throw CollectiblesStoreError(err + custNum + "\n");
         }
      }
   }
   return true;
}


//------------------- Process Customer ------------------------------------
// Parses a given input string returning data from a customer
// PreConditions : The input must be comma space seperated
// Postconditions: returns a string representation of the data following
//                 the comma
std::string CustomerManager::processCustomer(std::string& curLine) const
{
   int startPosition = 0;
   int endPosition = 0;

   int curLineLength = curLine.length();

   if (curLine == "" || startPosition > curLineLength) {
      return "";
   }

   // format {, data} position 2 is the first char of the data
   curLineLength = curLine.length();
   while (endPosition < curLineLength &&
      curLine[endPosition] != ',') {

      endPosition++;
   }

   std::string data;

   if (endPosition == curLine.length()) {
      data = curLine.substr(startPosition, endPosition);
      // to handle deletion appropriately
      endPosition = curLine.length();
   }
   else {
      data = curLine.substr(startPosition, endPosition);
      // to handle deletion appropriately
      endPosition += 2;
   }

   // update the instructions to get the next piece of data
   curLine.erase(0, endPosition);
   return data;
}


//------------------- hashCustomer ------------------------------------
// Returns an integer hash from a customer's key, their customer number
// PreConditions : The customer number must be valid
// Postconditions: returns a string representation of the data following
//                 the comma
int CustomerManager::hashCustomer(std::string customerNumber) const
{

   return std::stoi(customerNumber);
}


//--------------------- validCustomerHash --------------------------------
// Checks if the hash is in the correct range
// Postconditions: returns true if the hash is in range and false otherwise
bool CustomerManager::validCustomerHash(int customerIndex) const
{
   std::string err = "Customer cannot be accessed at ";
   if ((customerIndex >= 0) && (customerIndex < NUM_CUSTOMERS)) {
      return true;
   }
   else {
      std::string num;
      num.push_back(customerIndex);
      throw CollectiblesStoreError(err + num);
      return false;
   }
}


//-------------------------- Default Constructor ---------------------------
// Creates a customerManager capable of tracking NUM_CUSTOMER customers
// Preconditions : the NUM_CUSTOMERS must be greater than 1
// Postconditions: a new customer manager is created 
CustomerManager::CustomerManager() :
   customerLog_(nullptr)
{

   customerLog_ = new HashableObject * [NUM_CUSTOMERS];

   for (int i = 0; i < NUM_CUSTOMERS; i++) {
      customerLog_[i] = nullptr;
   }
}


//-------------------------- Destructor -----------------------------------
// Frees any dynamic memory associated with the customer manager class
// Preconditions : the customer must be capable of freeing its own 
//                 dynamic memory
// Postconditions: frees the memory associated with the customer manager
CustomerManager::~CustomerManager()
{
   for (int i = 0; i < NUM_CUSTOMERS; i++) {
      delete customerLog_[i];
      customerLog_[i] = nullptr;
   }
   delete[] customerLog_;
}


//-------------------------- FillCustomerLog -------------------------------
// Fills the customer log from a given file. If any information is invalid
// an error is thrown to the cout and the file continues to be processed
// Preconditions : Assumes no two customers are in the file with the same
//                 customer number
// Postconditions: The customer list is filled from the file and any errors
//                 are thrown to cout
void CustomerManager::fillCustomerLog(std::ifstream& readFrom)
{
   std::string err1 = "Invalid Customer ";
   std::string curCust = "";
   while (readFrom.peek() != EOF) {
      
      std::getline(readFrom, curCust);
      std::string customerNumberString = processCustomer(curCust);
      // we know the first is the customer number
      int customerNumber;
      try {
         validCustomerNumber(customerNumberString);
      }
      catch (CollectiblesStoreError err) {
         std::cout << err.what() << std::endl;
         continue;
      }

      customerNumber = std::stoi(customerNumberString);

      int custIndex;
      try {
         custIndex = hashCustomer(customerNumberString);
      }
      catch (CollectiblesStoreError err) {
         std::cout << err.what() << std::endl;
         continue;
      }

      std::string custName = processCustomer(curCust);
      HashableObject* newCustomer = new Customer(customerNumber, custName);
      customerLog_[custIndex] = newCustomer;
   }
}


//-------------------------- findCustomer ---------------------------------
// Given the customer ID the customer manager will find a customer in the
// customer list
// 
// Postconditions: If the customer is found it is returned to the caller
//                 if the customer id is invalid or the customer cannot
//                 be found an error is thrown
const Customer* CustomerManager::findCustomer(std::string ID)
{
   std::string err = "No customer exists with ID ";

   // can throw
   validCustomerNumber(ID);

   int customerIndex = hashCustomer(ID);

   // can throw
   if (validCustomerHash(customerIndex)) {
      
      if (customerLog_[customerIndex] == nullptr) {
         throw CollectiblesStoreError(err + ID);
      }
      else {
         return static_cast<const Customer*>(customerLog_[customerIndex]);
      }
   }
   return nullptr;
}