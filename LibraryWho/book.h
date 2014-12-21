//
//  library.h
//  Library
//
//  Created by Whoami on 14/12/14.
//  Copyright (c) 2014年 Jiyuan Liu.
//

#ifndef __Library__book__
#define __Library__book__

#include <time.h>
#include "common.h"

struct BorrowNode {
    unsigned rid;
    BorrowNode* nextReader;
    BorrowNode();
};

class Book {
private:
    ISBN isbn;
public:
    string name;
    string author;
    Date date;
    unsigned price;
    int quantity;
    BorrowNode* readers;
    
    Book(ISBN isbnIn);
    void inputPrice(double priceIn);
    double outputPrice();
    bool readerReturn(unsigned rRid);        //0.fail, 1.success.
    ISBN getISBN();
};

#endif /* defined(__Library__library__) */
