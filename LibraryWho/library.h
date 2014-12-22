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
    unsigned readerNumber;
    unsigned ridCount;
    ReaderNode* readerPool;
    BookNode* bookPool;
    
    int buildReaderPool(string filePath);   //todo
    int buildBookPool(string filePath);     //Import the book pool from *.lwb.
    int exportBookPool(string filePath);    //Export the book pool into *.lwb.
    int exportReaderPool(string filePath);  //Export the reader pool into *.lwr.
    
public:
    Book* bookNow;
    Reader* readerNow;
    
    Library();
    ~Library();
    int importBooks(string filePath, int num);       //-1.Fail, 0.Success
    int printAllBooks(string filePath);     //-1.Fail, 0.Success need to change
    int printAllReaders(string filePath);   //-1.Fail, 0.Success
    int buildALibrary(string filePath);     //0.Success, 1.Book fail, 2.Reader fail.
    int addReaders(int num, int level);     //0.Success, 1-3, Fail.
    bool ISBN_search();                     //0.Fail, 1.Success
    bool BOOKNAME_search();                 //0.Fail, 1.Success
    void printBookInfo();                   //Print the information of the book.
    void printReaderInfo();                 //Print the information of the reader.
    int borrowBook();                       //Reader now borrow the book now.
    int returnBook();                       //Reader now return the book now.   todo
    int exportTheLibrary(string filepath);  //0.Success, 1.Book fail, 2.Reader fail.
};

#endif /* defined(__LibraryWho__library__) */