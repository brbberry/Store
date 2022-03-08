#include "CollectiblesStoreError.h"

CollectiblesStoreError::CollectiblesStoreError(const std::string& StoreErr) :
   std::logic_error("StoreError: " + StoreErr)
{
}
