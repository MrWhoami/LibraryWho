//
//  node.h
//  LibraryWho
//
//  Created by Jiyuan Liu on 14/12/28.
//  Copyright (c) 2014年 Whoami. All rights reserved.
//

#ifndef LibraryWho_node_h
#define LibraryWho_node_h

#include "common.h"
#include "book.h"
#include "reader.h"

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

#endif
