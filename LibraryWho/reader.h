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
    BookBorrowed* nextBook;
    BookBorrowed() {
        theBook = NULL;
        nextBook = NULL;
    }
};

class Reader {
private:
    BookBorrowed *bookBorrowed;
    unsigned rid;
    int borrowed;
public:
    string name;
    int level;
    string contact;
    
    Reader(unsigned rid);
    ~Reader();
    unsigned getRid();
    int getNumber();
    int getBook(Book** &bookBorrowed);
    bool borrowNew(Book* newBook);
    bool returnOld(Book* oldBook);
};

#endif /* defined(__LibraryWho__reader__) */
