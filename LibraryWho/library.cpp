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
    double price;
    char endTest;
    BookNode* p;
    endTest = fin.get();                    //Get a charactor to judge if it is the end of the file.
    while (endTest != EOF) {
        fin >> reading;                     //Read No.
        fin >> buffer;                      //Read name into the buffer.
        ISBN tmpISBN;
        fin >> reading;                     //Read the next string.
        while (!(tmpISBN << reading)) {     //If this string is not an ISBN code.
            buffer += "+";                  //Add this string to the name.
            buffer += reading;
            fin >> reading;                 //Read another string.
        }
        p = bookPool;                       //If this string is an ISBN code.
        bookPool = new BookNode(tmpISBN);   //Create a new book node with this ISBN code.
        bookPool->nextBook = p;
        bookPool->book->name = buffer;      //Input its name.
        fin >> buffer;                      //Input the author.
        Date tmpDate;
        fin >> reading;                     //Input another string.
        while (!(tmpDate << reading)) {     //If this string is not a Date string.
            buffer += "+";                  //Add this string to the author.
            buffer += reading;
            fin >> reading;                 //Read another string.
        }
        bookPool->book->date = tmpDate;     //If this string is a Date code.
        bookPool->book->author = buffer;    //Input the author and the date to the new node.
        fin >> price;                       //Read the price.
        bookPool->book->inputPrice(price);  //Input the price to the new node.
        bookNumber++;
        endTest = fin.get();                //Get another charactor to judge if it ios the end of the file.
    }
    fin.close();
    return 0;
}

int Library::printAllBooks(string filePath) {
    ofstream fout(filePath);
    if (!fout) return -1;
    BookNode *p = bookPool;
    int i = 1;
    while (i <= bookNumber) {
        fout << i << ".  ";
        fout << p->book->name;
        fout << p->book->getISBN().group1 << '-';
        fout << p->book->getISBN().group2 << '-';
        fout << p->book->getISBN().group3 << '-';
        fout << p->book->getISBN().group4 << '-';
        fout << p->book->getISBN().group5 << ' ';
        fout << p->book->author << ' ';
        fout << p->book->date.year << '-';
        fout << p->book->date.month << '-';
        fout << p->book->date.day << ' ';
        fout << p->book->outputPrice() << '\n';
    }
    fout.close();
    return 0;
}

Book* Library::ISBN_search(){
    string look_for;
    printf("Please code the book'ISBN that you're looking for:\n");
    cin>>look_for;
    ISBN fuck;
    fuck << look_for;
    BookNode * test;
    for( test = bookPool; test != NULL; test = test->nextBook ){
        if(test->book->getISBN() == fuck){
            break;
        }
    }
    if(test == NULL){
        cout<<"Sorry, can't find a book whose ISBN is "<<look_for<<endl;
        return NULL;
    } else {
        return test->book;
    }
}

Book* Library::BOOKNAME_search(string name){
    string look_for;
    printf("Please code the book'name that you're looking for:\n");
    cin>>look_for;
    BookNode * test;
    for( test = bookPool; test != NULL; test = test->nextBook ){
        if(look_for.compare(test->book->name)==0){
            break;
        }
    }
    if(test == NULL){
        cout<< "Sorry, can't find a book whose name is " << look_for << endl;
        return NULL;
    } else {
        return test->book;
    }
}