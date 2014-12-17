//
//  Library.h
//  LibraryWho
//
//  Created by Whoami on 14/12/16.
//  Copyright (c) 2014年 Whoami.
//
//  TODO: Add book addition function.

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
    Library();
    ~Library();
    int buildALibrary(string filePath);
    int printAllBooks(string filePath);
    Book* ISBN_search(ISBN Isbn);
    Book* BOOKNAME_search(string name);
};

#endif /* defined(__LibraryWho__library__) */