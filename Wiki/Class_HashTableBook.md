# Class HashTableBook
## General Description
`class HashTableBook` is a hash table to speed up the ISBN code searching of books.
## Location
`class HashTableBook` is declared in **HashTable.h** and is defined in **HashTable.cpp**.  
## Variables
    private:
    int divisor
    ChainNode<BookNode*>** head  
`int divisor` serves just like its name.  
`ChainNode<BookNode*>** head` is the head pointer pointing to a dynamic array (the hash table).  
## Function  
    int findPosition(ISBN)
    bool searchBook(ISBN &)
    bool searchBook(ISBN &, BookNode**)
    bool insertBook(BookNode*)
    bool removeBook(BookNode*)  
Just like their names.