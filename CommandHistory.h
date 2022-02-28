// Blake Berry
// 02/22/2022
// Homework 4 Design
// This file is an interface for the CommandHistory class. The CommandHistory
// class inherits from the command interface. The CommandHistory class
// is responsible for the end - to - end execution of displaying the stores
// entire customer transaction history
//-----------------------------------------------------------------------------

#pragma once
#include "Command.h"
class CommandHistory : public Command
{
public:

   //-------------------------- constructor -----------------------------------
// creates a CommandHistroy with a given string Indicator
// Postconditions: A CommandHistory is created
   CommandHistory(std::string type = "H");


   //-------------------------- destructor -----------------------------------
   // Frees any dynamic memory associated with the Command object
   // Postconditions: The command is freed of any dynamic memory
   ~CommandHistory();

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
   // in the command class's field (H for commandHistroy)
   // Postconditions: The commandBuy object is created and returned
   virtual const Command* create(std::string type);


   //-------------------------- Execute -----------------------------------
   // Facilitates the display of the entire store transaction history.
   // If there is no such customers or transaction history an exception
   // is thrown
   // Postconditions: The entire transaction history for a given customer is
   //                 displayed in chronolgoical order.
   // 
   //                 If there is no such customers or transaction history an 
   //                 exception is thrown
   virtual void execute(TransactionManager& tManager,
      ItemsManager& iManager,
      CustomerManager& cManager,
      std::string command) const;
   //PSUEDOCODE
   /*
      the transaction manager to display the entire stores transation
      history

   */

};

