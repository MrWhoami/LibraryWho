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

int Library::buildALibrary(string filePath) {
    ifstream fin(filePath);
    if (!fin) return -1;
    string reading;
    string buffer;
    char endTest;
    BookNode* p;
    endTest = fin.get();
    while (endTest != EOF) {
        fin >> reading;
        fin >> buffer;
        ISBN tmpISBN;
        fin >> reading;
        if(tmpISBN << reading) {
            p = bookPool;
            bookPool = new BookNode(tmpISBN);
            bookPool->nextBook = p;
            bookPool->book->name = buffer;
        } else {
            buffer += "+";
            buffer += reading;
            fin >> reading;
        }
    }
    return 0;
}