//
//  Library.h
//  LibraryWho
//
//  Created by Whoami on 14/12/16.
//  Copyright (c) 2014年 Jiyuan Liu.
//

#ifndef __LibraryWho__library__
#define __LibraryWho__library__

#include <iostream>
#include "common.h"
#include "reader.h"
#include "book.h"
#include <fstream>

struct ReaderNode {
    Reader *reader;
    ReaderNode *nextReader;
    ReaderNode (unsigned ridIn){
        reader = new Reader(ridIn);
        nextReader = NULL;
    }
    ~ReaderNode(){
        delete reader;
    }
};

struct BookNode {
    Book *book;
    BookNode *nextBook;
    BookNode(ISBN isbnIn){
        book = new Book(isbnIn);
        nextBook = NULL;
    }
    ~BookNode() {
        delete book;
    }
};

class Library {
    unsigned bookNumber;
    unsigned userNumber;
    ReaderNode* readerPool;
    BookNode* bookPool;
    
public:
    Book* bookNow;
    Reader* readerNow;
    
    Library();
    ~Library();
    int buildALibrary(string filePath);
    int printAllBooks(string filePath);
    bool ISBN_search();
    bool BOOKNAME_search();
    void printBookInfo();
};

#endif /* defined(__LibraryWho__library__) */