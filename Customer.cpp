#include "Customer.h"

Customer::Customer(int customerNumber, std::string customerName) :
   HashableObject(std::to_string(customerNumber)),
   customerNumber_(customerNumber),
   customerName_(customerName)
{
}



std::string Customer::getName() const
{
   return customerName_;
}

/*
int main() {
   return 0;
}
*/