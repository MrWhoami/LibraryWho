//
//  Library.cpp
//  LibraryWho
//
//  Created by Whoami on 14/12/16.
//  Copyright (c) 2014年 Whoami.
//

#include "library.h"

Library::Library() {
    bookNumber = 0;
    userNumber = 0;
    readerPool = NULL;
    bookPool = NULL;
}

Library::~Library() {
    while (readerPool != NULL) {
        ReaderNode *p = readerPool;
        readerPool = readerPool->nextReader;
        delete p;
    }
    while (bookPool != NULL) {
        BookNode *p = bookPool;
        bookPool = bookPool->nextBook;
        delete p;
    }
}