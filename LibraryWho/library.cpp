//
//  Library.cpp
//  LibraryWho
//
//  Created by Whoami on 14/12/16.
//  Copyright (c) 2014年 Jiyuan Liu.
//

#include "library.h"

Library::Library() {
    bookNumber = 0;
    readerNumber = 0;
    ridCount = 0;
    readerPool = NULL;
    bookPool = NULL;
    readerNow = NULL;
    bookNow = NULL;
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
    string lastReading;
    double price;
    BookNode* p;
    fin >> reading;                         //Read the No.
    do {
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
        tmpDate.year = 0;
        tmpISBN.group1 = 0;
        lastReading = reading;
        fin >> reading;                     //Read the next No to judge if it is the end.
    } while (reading != lastReading);
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
        p = p->nextBook;
        i++;
    }
    fout.close();
    return 0;
}

bool Library::ISBN_search(){
    string look_for;
    printf("Please code the ISBN of the target book(978-x-xxx-xxxxx-x):\n");
    cin  >> look_for;
    ISBN fuck;
    if (!(fuck << look_for)){
        cout << "Invalid ISBN code. " << look_for << endl;
        return 0;
    }
    BookNode * test;
    for( test = bookPool; test != NULL; test = test->nextBook ){
        if(test->book->getISBN() == fuck){
            break;
        }
    }
    if(test == NULL){
        cout << " Sorry, we can't find a book whose ISBN is " << look_for << endl;
        return 0;
    } else {
        bookNow = test->book;
        return 1;
    }
}

bool Library::BOOKNAME_search(){
    string look_for;
    printf("Please input the name of the target book:\n");
    cin >> look_for;
    BookNode * test;
    for( test = bookPool; test != NULL; test = test->nextBook ){
        if(look_for.compare(test->book->name)==0){
            break;
        }
    }
    if(test == NULL){
        cout<< "Sorry, we can't find a book whose name is " << look_for << endl;
        return 0;
    } else {
        bookNow = test->book;
        return 1;
    }
}

void Library::printBookInfo() {
    if (bookNow == NULL) {
        cout << "You haven't got a book yet." << endl;
        return;
    }
    cout << "Book:        " << bookNow->name << endl;
    cout << "ISBN:        ";
    cout << bookNow->getISBN().group1 << '-';
    cout << bookNow->getISBN().group2 << '-';
    cout << bookNow->getISBN().group3 << '-';
    cout << bookNow->getISBN().group4 << '-';
    cout << bookNow->getISBN().group5 << endl;
    cout << "Author:       " << bookNow->author << endl;
    cout << "Publish Date: ";
    cout << bookNow->date.year << '-';
    cout << bookNow->date.month << '-';
    cout << bookNow->date.day << endl;
    cout << "Price:        " << bookNow->outputPrice() << endl;
}

int Library::addReaders(int num, int levelIn) {
    char code = 0;
    if (num < 1) {
        code = code+1;
    }
    if (levelIn < 1) {
        code = code+2;
    }
    if (code > 0) {
        return code;
    }
    string reading;
    for(int i=0; i<num; i++){
        ReaderNode* tmp = new ReaderNode(ridCount);
        cout << "No. " << tmp->reader->getRid() << endl;;
        cout << "Name: ";
        cin >> reading;
        tmp->reader->name = reading;
        tmp->reader->level = levelIn;
        cout << "Level: " << tmp->reader->level << endl;
        cout << "Email: ";
        cin >> reading;
        tmp->reader->email = reading;
        tmp->nextReader = readerPool;
        readerPool = tmp;
        readerNumber++;
        cout << endl;
    }
    return 0;
}

int Library::printAllReaders(string filePath){
    ofstream fout(filePath);
    if (!fout) return -1;
    ReaderNode *p = readerPool;
    int i = 1;
    while (i <= readerNumber) {
        fout << i << ".  ";
        fout << p->reader->name << ' ';
        fout << p->reader->level << ' ';
        fout << p->reader->email << ' ';
        int bookNum = p->reader->getNumber();
        fout << bookNum << ' ';
        ISBN* booksBorrowed = new ISBN[bookNum];
        p->reader->getBook(booksBorrowed);
        for (int j=0; j<bookNum; j++) {
            fout << booksBorrowed[i].group1 << '-';
            fout << booksBorrowed[i].group2 << '-';
            fout << booksBorrowed[i].group3 << '-';
            fout << booksBorrowed[i].group4 << '-';
            fout << booksBorrowed[i].group5 << ' ';
        }
        fout << '\n';
        p = p->nextReader;
        i++;
    }
    fout.close();
    return 0;
}
