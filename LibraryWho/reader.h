//
//  reader.h
//  LibraryWho
//
//  Created by Whoami on 14/12/15.
//  Copyright (c) 2014年 Whoami.
//

#ifndef __LibraryWho__reader__
#define __LibraryWho__reader__

#include "common.h"
#include "book.h"

struct BookBorrowed {
    Book *theBook;
    bool breakRule;
    BookBorrowed* nextBook;
    BookBorrowed() {
        theBook = NULL;
        breakRule = 0;
        nextBook = NULL;
    }
};

class reader {
private:
    BookBorrowed *bookBorrowed;
    unsigned rid;
    int borrowed;
public:
    string name;
    int level;
    string contact;
    
    reader(unsigned rid);
    ~reader();
    unsigned getRid();
    int getNumber();
    int getBook(Book** &bookBorrowed);
    bool borrowNew(Book* newBook);
    bool returnOld(Book* oldBook);
};

#endif /* defined(__LibraryWho__reader__) */
