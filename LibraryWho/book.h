//
//  library.h
//  Library
//
//  Created by Whoami on 14/12/14.
//  Copyright (c) 2014年 Whoami.
//

#ifndef __Library__book__
#define __Library__book__

#include <time.h>
#include "common.h"
#include "queue.h"

class BorrowNode {
public:
    Date borrowDate;
    bool renew;
    unsigned rid;
    BorrowNode* nextReader;
    
    BorrowNode();
    Date returnDate();
};

class Book {
private:
    ISBN isbn;
public:
    string name;
    string writer;
    Date date;
    unsigned price;
    int quantity;
    BorrowNode* readers;
    
    Book(ISBN isbnIn);
    void inputPrice(double priceIn);
    void inputISBN(string isbnIn);
    void ruleBreaker(Queue<unsigned> &breakers);
    double outputPrice();
    int readerReturn(unsigned rRid);
};

#endif /* defined(__Library__library__) */
