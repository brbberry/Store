// Blake Berry
// 02/22/2022
// Homework 4 Design
// This file is an interface for the HashableTable class. The class maintains
// an array of HashableObject pointers and promotes quick access by using
// the HashableObjects hash to store the items in the array. The table is
// constructed from a given size. This hashtable only supports item retrievial.
// It is assumed that there are no collosions and therefore this hashtable does
// not support rehashing/resizing
//------------------------------------------------------------------------------

#pragma once
#include "HashableObject.h"


class HashTable
{

   HashableObject** table_; // an array of HashableObject pointers
   
   int capacity_;           // the number of possible elements
   int size_;               // how full the hashtable is


public:

   //------------------------- Constructor -----------------------------------
   // Creates a hashtable of size 26 by default
   // Postconditions: Creates a hashtable with 26 hashable items
   HashTable(int size = 26);
   // PSUEDOCODE
   /*
      size_ = size;
      capacity = 0;

      from 0 up to size
         set the table_ filled with nullptrs
   
   */


   //-------------------------- destructor -----------------------------------
   // Frees the memory associated with hashtable
   // Preconditions : the hashable object frees its own dynamically allocated
   //                 memory
   // Postconditions: The hashtable is cleared of all the dynamic memory that  
   //                 is associated
   ~HashTable();


   //-------------------------- insert -----------------------------------
   // Adds an item to the hashtable returning true if the insert was 
   // successful and false otherwise
   // Preconditions : the hash function and addition scheme needs to be
   //                 created by the derived classes
   // Postconditions: if the hashable object is added to the table true
   //                 is returned otherwise false is returned
   bool insert(HashableObject*& toAdd);
   // PSUEDOCODE
   /*
      check if the size is < the capacity 
         call hash from toAdd to get the index
      
         if the index is nullptr or the status is removed 
            add the item at that index
            return true
         else
            return false
      return false
   
   */

   //-------------------------- getValue -----------------------------------
   // From a given key a value is returned if it exists
   // Postconditions: a constant Hashable object pointer is returned from a key
   const HashableObject* getValue(HashableObject*& toGet);


   /*
   //-------------------------- remove -----------------------------------
   // From a given key a value is returned if it exists
   // Precondition  : the hashable object has to have the ability to hash
   // Postconditions: a constant Hashable object pointer is returned from a key
   bool remove(HashableObject*& toRemove);
   // PSUEDOCODE
   /*
      call hash from toRemove to get the index

      if the index is nullptr or the status is removed
         return false
      else
         call the HashableObjects remove function
         return true

   */
};