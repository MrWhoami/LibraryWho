//
//  reader.cpp
//  LibraryWho
//
//  Created by Whoami on 14/12/15.
//  Copyright (c) 2014年 Whoami.
//

#include "reader.h"


Reader::Reader(unsigned ridIn){
    bookBorrowed = NULL;
    rid = ridIn;
    borrowed = 0;
    level = 1;
}

Reader::~Reader(){
    while (bookBorrowed != NULL) {
        BookBorrowed* p = bookBorrowed;
        bookBorrowed = bookBorrowed->nextBook;
        delete p;
    }
}

