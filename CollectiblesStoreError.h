// Blake Berry
// 02/22/2022
// Homework4 Design
// This is a CollectiblesStoreErro which is to be thrown during store 
// opperations to provide context to the client about what went wrong
//------------------------------------------------------------------------------
#pragma once
#include<stdexcept>
#include<string>

class CollectiblesStoreError : public std::logic_error
{
public:

   //------------------------ constructor -------------------------------------
   // Constructs an error with a specified error message that better 
   // describes why an error was thrown
   // Postconditions: creates an error with a string that clearly provides
   //                 the client more information about an error that occured 
   //                 during store operations
   CollectiblesStoreError(const std::string& StoreErr = "");
};
