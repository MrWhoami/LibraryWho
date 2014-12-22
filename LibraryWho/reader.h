//
//  reader.h
//  LibraryWho
//
//  Created by Whoami on 14/12/15.
//  Copyright (c) 2014年 Jiyuan Liu.
//

#ifndef __LibraryWho__reader__
#define __LibraryWho__reader__

#include "common.h"

class BookBorrowed {
public:
    ISBN theBook;
    Date borrowDate;
    bool renew;
    BookBorrowed* nextBook;
    
    BookBorrowed() {
        nextBook = NULL;
        borrowDate.year = 2000;
        borrowDate.month = 1;
        borrowDate.day = 1;
        renew = 0;
    }
    Date returnDate();
};

class Reader {
private:
    BookBorrowed *bookBorrowed;
    unsigned rid;
    int borrowed;
    
public:
    string name;
    int level;
    string email;
    
    Reader(unsigned rid);
    ~Reader();
    void importData(ISBN* isbnIn, Date* dateIn, bool* renewIn, int bookNum, int borrowedIn);           //Used to import backup data.
    unsigned getRid();
    int getNumber();
    int getBorrowed();
    int getBook(ISBN* &borrowedList);
    int getData(Date* &borrowedList);
    int getRenew(bool* &borrowedList);
    int borrowNew(ISBN newBook);           //0.Success, 1.Level limited, 2.Already borrowed.
    int returnOld(ISBN oldBook);           //0:Success, 1.No such book, 2.Broken the rule.
};

#endif /* defined(__LibraryWho__reader__) */
