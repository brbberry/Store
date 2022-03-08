#include "CollectionFactory.h"

int CollectionFactory::hashCollectible(std::string collectionType) const
{
   return collectionType[0] - 'A';
}

bool CollectionFactory::validCollectibleHash(int collectionIndex) const
{
   if (collectionIndex < FACTORY_SIZE && collectionIndex >= 0) {
      return true;
   }
   return false;
}

CollectionFactory::CollectionFactory(int size) :
   itemsFactory_(nullptr),
   size_(size)
{
   if (size_ <= 0 || size_ > FACTORY_SIZE) {
      //throw error
   }
   else {
      itemsFactory_ = new HashableObject * [size_];
      for (int i = 0; i < size; i++) {
         itemsFactory_[i] = nullptr;
      }
   }

   HashableObject* coin = new Coin();
   HashableObject* comic = new Comic();
   HashableObject* sportsCard = new SportsCard();

   int coinIndex = hashCollectible(coin->getID());
   if (validCollectibleHash(coinIndex)) {
      if (itemsFactory_[coinIndex] == nullptr) {
         itemsFactory_[coinIndex] = coin;
      }
   }
   int comicIndex = hashCollectible(comic->getID());
   if (validCollectibleHash(comicIndex)) {
      if (itemsFactory_[comicIndex] == nullptr) {
         itemsFactory_[comicIndex] = comic;
      }
   }
   int sportsCardIndex = hashCollectible(sportsCard->getID());
   if (validCollectibleHash(sportsCardIndex)) {
      if (itemsFactory_[sportsCardIndex] == nullptr) {
         itemsFactory_[sportsCardIndex] = sportsCard;
      }
   }

}

CollectionFactory::~CollectionFactory()
{
   for (int i = 0; i < size_; i++) {
      delete itemsFactory_[i];
      itemsFactory_[i] = nullptr;
   }
   delete[] itemsFactory_;
}

// possibly adjust to fill entire coin
const Collectible* CollectionFactory::create(std::string key) const
{
   // possibly make a get type method -- just takes the first Char M so its ", " formatted still

   int collectibleIndex = hashCollectible(key);
   if (validCollectibleHash(collectibleIndex)) {
      if (itemsFactory_[collectibleIndex] != nullptr) {
         Collectible* found = static_cast<Collectible*>(itemsFactory_[collectibleIndex]);

         return found;
      }
   }
   return nullptr;
}

/*
int main() {

   CollectionFactory* fact = new CollectionFactory();
   const Collectible* fromTheFact = fact->create("M");
   const Collectible* filledIn = fromTheFact->create(", 1913, 70, Liberty Nickel");
   filledIn->print();
   delete filledIn;
   delete fact;
   return 0;
}
*/