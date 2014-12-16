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

struct BookBorrowed {
    ISBN theBook;
    BookBorrowed* nextBook;
    BookBorrowed() {
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
    int getBook(ISBN* &bookBorrowed);
    bool borrowNew(ISBN newBook);
    bool returnOld(ISBN oldBook);
};

#endif /* defined(__LibraryWho__reader__) */
