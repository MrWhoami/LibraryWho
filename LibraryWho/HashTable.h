//
//  HashTable.h
//  LibraryWho
//
//  Created by Jiyuan Liu on 14/12/28.
//  Copyright (c) 2014年 Jiyuan Liu. All rights reserved.
//

#ifndef __LibraryWho__HashTable__
#define __LibraryWho__HashTable__

#include "node.h"

template <class T>
class ChainNode {           //Hash table chain node.
public:
    T data;
    ChainNode* next;
};

class HashTableBook {       //Hash table for ISBN of the book.
private:
    int divisor;
    ChainNode<BookNode*>** head;
    int findPosition(ISBN isbnIn);  //Return the group of the target.
    
public:
    HashTableBook(int divisor);
    ~HashTableBook();
    bool searchBook(ISBN &isbnIn);
    bool searchBook(ISBN isbnIn, BookNode** target);
    bool insertBook(BookNode* target);
    bool removeBook(BookNode* target);
};

#endif /* defined(__LibraryWho__HashTable__) */
