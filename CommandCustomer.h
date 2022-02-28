// Blake Berry
// 02/22/2022
// Homework 4 Design
// This file is an interface for the CommandCustomerclass. The CommandCustomer
// class inherits from the command interface. The CommandCustomer class
// is responsible for the end - to - end execution of displaying a customers
// transaction history with the store
//-----------------------------------------------------------------------------

#pragma once
#include "Command.h"
class CommandCustomer : public Command
{

public:

   //-------------------------- constructor -----------------------------------
   // creates a CommandCustomer with a given string Indicator
   // Postconditions: A CommandCustomer is created
   CommandCustomer(std::string type = "C");


   //-------------------------- destructor -----------------------------------
   // Frees any dynamic memory associated with the Command object
   // Postconditions: The command is freed of any dynamic memory
   ~CommandCustomer();

   //-------------------------------- Hash -----------------------------------
   // generates an int from the value that the Command holds
   // Preconditions : Assumes that the key is a capital ASCII value A-Z
   // Postconditions: an integer is returned based off the value held by the 
   //                 command object
   int hash() const;
   //PSUEDOCODE
   /*
      returns ASCII value for command - ASCII A

   */

   //-------------------------- Create -----------------------------------
   // Creates a specific CommandBuy based off a string type that is stored
   // in the command class's field (C for commandCustomer)
   // Postconditions: The commandBuy object is created and returned
   virtual const Command* create(std::string type ="C");


   //-------------------------- Execute -----------------------------------
   // Facilitates the display of a customer entire transaction history.
   // If there is no such customer or transaction history an exception
   // is thrown
   // Postconditions: The entire transaction history for a given customer is
   //                 displayed in chronolgoical order
   // 
   //                 If there is no such customer or transaction history an 
   //                 exception is thrown
   virtual void execute(TransactionManager& tManager,
      ItemsManager& iManager,
      CustomerManager& cManager,
      std::string command) const;
   //PSUEDOCODE
   /*
      uses the customer manager to check if the customer exists
      
      the transaction manager is given a customer to display their 
      transactionHistroy
         
   */
};

