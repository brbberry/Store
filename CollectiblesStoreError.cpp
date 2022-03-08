// Blake Berry
// 03/08/2022
// Homework 4 
// This is a CollectiblesStoreError which is to be thrown during store 
// opperations to provide context to the client about what went wrong
//------------------------------------------------------------------------------

#include "CollectiblesStoreError.h"


//------------------------ constructor -------------------------------------
// Constructs an error with a specified error message that better 
// describes why an error was thrown
// Postconditions: creates an error with a string that clearly provides
//                 the client more information about an error that occured 
//                 during store operations
CollectiblesStoreError::CollectiblesStoreError(const std::string& StoreErr) :
   std::logic_error("StoreError: " + StoreErr)
{
}
