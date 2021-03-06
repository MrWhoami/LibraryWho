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
#include <fstream>
#include "common.h"
#include "reader.h"
#include "book.h"
#include "node.h"
#include "HashTable.h"

class Library {
    unsigned bookNumber;
    unsigned readerNumber;
    unsigned ridCount;
    ReaderNode* readerPool;
    BookNode* bookPool;
    HashTableBook bookTable;
    
    int buildReaderPool(string filePath);   //Import the reader pool from *.lwr.
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
    bool addBooks();                        //0.Fail, 1.Success
    bool ISBN_search();                     //0.Fail, 1.Success
    bool BOOKNAME_search();                 //0.Fail, 1.Success
    void BOOKNAMEpart_search();             //0.Fail, 1.Success
    void printBookInfo();                   //Print the information of the book.
    void printReaderInfo();                 //Print the information of the reader.
    int borrowBook();                       //Reader now borrow the book now.
    int returnBook();                       //Reader now return the book now.
    int exportTheLibrary(string filepath);  //0.Success, 1.Book fail, 2.Reader fail.
    void AUTHORpart_search();               //Search the book with part of its author name.
    bool RID_search();                      //0.Fail, 1.Success
    bool READERNAME_search();               //0.Fail, 1.Success
    bool EMAIL_search();                    //0.Fail, 1.Success
    int renewBook();                        //0.Success, 1.No such book, 2.Already renewed, 4.Broken the rule.
    unsigned getBookNumber();               //Return the kind number of books.
    unsigned getReaderNumber();             //Return the reader number.
};

#endif /* defined(__LibraryWho__library__) */