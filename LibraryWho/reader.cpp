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

unsigned Reader::getRid(){
    return rid;
}

int Reader::getNumber(){
    BookBorrowed *p = bookBorrowed;
    int num = 0;
    while ( p!= NULL) {
        num++;
        p = p->nextBook;
    }
    return num;
}

bool Reader::borrowNew(Book* newBook){
    if (getNumber() == level) {
        return 0;
    }
    if (bookBorrowed == NULL) {
        bookBorrowed = new BookBorrowed;
        bookBorrowed->theBook = newBook;
    } else {
        BookBorrowed* p= bookBorrowed;
        while (p->nextBook != NULL) {
            if (p->theBook == newBook) {
                return 0;
            }
            p = p->nextBook;
        }
        p->nextBook = new BookBorrowed;
        p->nextBook->theBook = newBook;
    }
    return 1;
}