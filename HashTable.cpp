#include "HashTable.h"

HashTable::HashTable(int size) :
   table_(nullptr),
   capacity_(0),
   size_(size)
{
   table_ = new HashableObject*[size];
   for (int i = 0; i < size; i++) {
      table_[i] = nullptr;
   }
}

HashTable::~HashTable()
{
   for (int i = 0; i < size_; i++) {
      delete table_[i];
      table_[i] = nullptr;
   }
   delete[] table_;
}

bool HashTable::insert(HashableObject*& toAdd)
{
   int index = toAdd->hash();
   if (table_[index] == nullptr) {
      table_[index] = toAdd;
      return true;
   }
 
   return false;
}

const HashableObject* HashTable::getValue(HashableObject*& toGet)
{
   int index = toGet->hash();
   if (table_[index] == nullptr) {
      return nullptr;
   }
   else {
      return table_[index];
   }
}

int main() {
   return 0;
}