//
//  library.h
//  LibraryWho
//
//  Created by Whoami on 14/12/14.
//  Copyright (c) 2014年 Jiyuan Liu.
//

#ifndef __LibraryWho__book__
#define __LibraryWho__book__

#include "common.h"

struct BorrowNode {
    unsigned rid;
    BorrowNode* nextReader;
    BorrowNode();
};

class Book {
private:
    ISBN isbn;
    BorrowNode* readers;
    
public:
    string name;
    string author;
    Date date;
    unsigned price;
    int quantity;
    
    Book(ISBN isbnIn);
    ~Book();
    int getTotal();
    int getReaderNum();
    int getReaders(unsigned* &rid);
    int borrowBook(unsigned rid);            //0.Success, 1.No book, 2.Already borrowed,
    int returnBook(unsigned rid);            //0.Success, 1.Not borrowed.
    void inputPrice(double priceIn);
    double outputPrice();
//  bool readerReturn(unsigned rRid);
    ISBN getISBN();
};

#endif /* defined(__LibraryWho__library__) */
