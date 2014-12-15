//
//  library.h
//  Library
//
//  Created by Whoami on 14/12/14.
//  Copyright (c) 2014年 Whoami.
//

#ifndef __Library__book__
#define __Library__book__

#include <string>
#include <time.h>
using namespace std;
#include "queue.h"

struct Date {
    short year;
    short month;
    short day;
};

struct ISBN {
    unsigned group1;
    unsigned group2;
    unsigned group3;
    unsigned group4;
    unsigned group5;
};

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
public:
    string name;
    ISBN isbn;
    string writer;
    Date date;
    unsigned price;
    int quantity;
    BorrowNode* readers;
    
    Book();
    void inputPrice(double priceIn);
    void inputISBN(string isbnIn);
    void ruleBreaker(Queue<unsigned> &breakers);
    double outputPrice();
};

#endif /* defined(__Library__library__) */
