//
//  library.h
//  LibraryWho
//
//  Created by Whoami on 14/12/14.
//  Copyright (c) 2014年 Jiyuan Liu.
//

#ifndef __LibraryWho__book__
#define __LibraryWho__book__

#include "common.h"

struct BorrowNode {
    unsigned rid;
    BorrowNode* nextReader;
    BorrowNode();
};

class Book {
private:
    ISBN isbn;
    BorrowNode* readers;
    
public:
    string name;
    string author;
    Date date;
    unsigned price;
    int quantity;
    
    Book(ISBN isbnIn);                       //Must create a book with an ISBN code.
    ~Book();
    int getTotal();                          //Get the total book number.
    int getReaderNum();                      //Return reader number.
    int getReaders(unsigned* &rid);          //Get the reader list. Return reader number.
    int borrowBook(unsigned rid);            //0.Success, 1.No book, 2.Already borrowed,
    int returnBook(unsigned rid);            //0.Success, 1.Not borrowed.
    void inputPrice(double priceIn);         //Input the price in double.
    double outputPrice();                    //Output the price in double.
    ISBN getISBN();                          //Get the ISBN code of the book.
};

#endif /* defined(__LibraryWho__library__) */
