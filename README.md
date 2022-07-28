# Description
To simulate a collectibles store a collectibles store class was created from a template store class.
The Store has three manager classes, one to manage the transaction history and logging – called
the TransactionManager, one to manage the list of customers and customer information – called
the CsutomerManager, and one to manage in inventory of collectibles – called the ItemsManager.
The store is operated using a given set of commands. The commands are managed by a
command factory that uses the store managers to collectively execute a given function that the
store needs to accomplish. If any command executed is found to be invalid, an
error will be thrown and managed by the store itself.
The TransactionManager receives information from both the CustomerManager and
ItemsManager logging transaction for a given customer. The TransactionManager stores a list of
transaction by Customer name in alphabetic order with their transaction in chronological order.
The ItemsManager and CustomerManager both communicate to the store if any invalid item or
customer is to be used in a command. The ItemsManager can easily generate items for quick
look up to verify that items are valid and create an item quickly. The items manager also stores
each item type separately in a list in sorted order. The CustomerManager can quickly look up if a
customer is in a list of known customers.
The Commands that the store can execute can be easily extended through the addition of new
commands. The commands are generated from a quick look up and executed using the
managers.

*description of main:*
The store initializes its customers and items from a given file. Then, while the list of commands
the store must execute is not empty (eof), the store will use its command factory to process each
command. An output to the console will not be made for successful transaction unless a given
command specifically demands an output to the console. If an invalid transaction if attempted an
error message will be displayed to the console and the store will move on to processing the next
command if possible



## Error Handeling
*If a store attempts to sell or buy something from an individual then an error will be thrown
*If a store attempts to sell or buy an item that is not supported by the store or has invalid
properties, an error will be thrown
*If customer history for a customer that does not exist is requested an error will be thrown

##Input
*The customer list and store inventory will be initialized from a file. The file is assumed to be
properly formatted however may contain invalid data – the file contents are checked for
validity
*The commands that the store will execute are initialized from a file. The file is assumed to be
properly formatted however may contain invalid data – the file contents are checked for
validity
