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

int Library::importBooks(string filePath, int num) {
    ifstream fin(filePath);
    if (!fin) return -1;
    string reading;
    string buffer;
    double price;
    BookNode* p;
    fin >> buffer;                          //Read the No.
    reading = buffer;
    fin >> buffer;                          //Read name into the buffer.
    while (reading != buffer) {
        ISBN tmpISBN;
        fin >> reading;                     //Read the next string.
        while (!(tmpISBN << reading)) {     //If this string is not an ISBN code.
            buffer += " ";                  //Add this string to the name.
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
            buffer += " ";                  //Add this string to the author.
            buffer += reading;
            fin >> reading;                 //Read another string.
        }
        bookPool->book->date = tmpDate;     //If this string is a Date code.
        bookPool->book->author = buffer;    //Input the author and the date to the new node.
        fin >> price;                       //Read the price.
        bookPool->book->inputPrice(price);  //Input the price to the new node.
        bookPool->book->quantity = num;     //Input the quantity of the new node.
        bookNumber++;
        tmpDate.year = 0;
        tmpISBN.group1 = 0;
        fin >> buffer;                          //Read the No.
        reading = buffer;
        fin >> buffer;                          //Read name into the buffer.
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
        p = p->nextBook;
        i++;
    }
    fout.close();
    return 0;
}

bool Library::ISBN_search() {
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

bool Library::BOOKNAME_search() {
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
    cout << "Storage:      " << bookNow->quantity << endl;
    int readerNum = bookNow->getReaderNum();
    unsigned* ridList = new unsigned[readerNum];
    bookNow->getReaders(ridList);
    cout << "Readers:      " << readerNum << endl;
    for (int i=0; i<readerNum; i++) {
        cout << ridList[i] << ' ';
    }
    cout << endl;
    cout << endl;
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
        ridCount++;
        cout << endl;
    }
    return 0;
}

int Library::printAllReaders(string filePath) {
    ofstream fout(filePath);
    if (!fout) return -1;
    ReaderNode *p = readerPool;
    int i = 1;
    while (i <= readerNumber) {
        fout << p->reader->getRid() << "  ";
        fout << p->reader->name << ' ';
        fout << p->reader->level << ' ';
        fout << p->reader->email << ' ';
        fout << p->reader->getBorrowed() << '\n';
        p = p->nextReader;
        i++;
    }
    fout.close();
    return 0;
}

void Library::printReaderInfo() {
    if (readerNow == NULL) {
        cout << "You haven't got a book yet." << endl;
        return;
    }
    cout << "RID:          " << readerNow->getRid() << endl;
    cout << "Name:         " << readerNow->name << endl;
    cout << "E-mail:       " << readerNow->email << endl;
    cout << "Level:        " << readerNow->level << endl;
    cout << "Book History: " << readerNow->getNumber() << endl;
    int bookNum = readerNow->getNumber();
    cout << "Now Reading:  " << bookNum << endl;
    cout << "ISBN        Date         Renew" << endl;
    ISBN* booksBorrowed = new ISBN[bookNum];
    Date* booksDate = new Date[bookNum];
    bool* booksRenew = new bool[bookNum];
    readerNow->getBook(booksBorrowed);
    readerNow->getData(booksDate);
    readerNow->getRenew(booksRenew);
    for (int j=0; j<bookNum; j++) {
        cout << booksBorrowed[j].group1 << '-';
        cout << booksBorrowed[j].group2 << '-';
        cout << booksBorrowed[j].group3 << '-';
        cout << booksBorrowed[j].group4 << '-';
        cout << booksBorrowed[j].group5 << ' ';
        cout << booksDate[j].year << '-';
        cout << booksDate[j].month << '-';
        cout << booksDate[j].day << ' ';
        cout << booksRenew[j] << '\n';
    }
    cout << endl;
}

int Library::exportReaderPool(string filePath) {
    ofstream fout(filePath);
    if (!fout) return 2;
    ReaderNode *p = readerPool;
    int i = 1;
    while (i <= readerNumber) {
        fout << p->reader->getRid() << ' ';
        fout << p->reader->name << ' ';
        fout << p->reader->level << ' ';
        fout << p->reader->email << ' ';
        fout << p->reader->getBorrowed() << ' ';
        int bookNum = p->reader->getNumber();
        fout << bookNum << ' ';
        ISBN* booksBorrowed = new ISBN[bookNum];
        Date* booksDate = new Date[bookNum];
        bool* booksRenew = new bool[bookNum];
        p->reader->getBook(booksBorrowed);
        p->reader->getData(booksDate);
        p->reader->getRenew(booksRenew);
        for (int j=0; j<bookNum; j++) {
            fout << booksBorrowed[j].group1 << '-';
            fout << booksBorrowed[j].group2 << '-';
            fout << booksBorrowed[j].group3 << '-';
            fout << booksBorrowed[j].group4 << '-';
            fout << booksBorrowed[j].group5 << ' ';
            fout << booksDate[j].year << '-';
            fout << booksDate[j].month << '-';
            fout << booksDate[j].day << ' ';
            fout << booksRenew[j] << ' ';
        }
        fout << '\n';
        delete [] booksRenew;
        delete [] booksDate;
        delete [] booksBorrowed;
        p = p->nextReader;
        i++;
    }
    fout.close();
    return 0;
}

int Library::exportBookPool(string filePath) {
    ofstream fout(filePath);
    if (!fout) return 1;
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
        fout << p->book->outputPrice() << ' ';
        fout << p->book->quantity << ' ';
        int bookNum = p->book->getReaderNum();
        unsigned* ridList = new unsigned[bookNum];
        p->book->getReaders(ridList);
        fout << bookNum << ' ';
        for (int j=0; j<bookNum; j++) {
            fout << ridList[j] << ' ';
        }
        fout << '\n';
        p = p->nextBook;
        i++;
    }
    fout.close();
    return 0;
}

int Library::exportTheLibrary(string filePath) {
    string path = filePath;
    if (path.back() != '/') {
        path += "/";
    }
    string pathLWR = path;
    string pathLWB = path;
    pathLWR += "backup.lwr";
    pathLWB += "backup.lwb";
    int runResult = 0;
    runResult += exportBookPool(pathLWB);
    runResult += exportReaderPool(pathLWR);
    return runResult;
}

int Library::buildALibrary(string filePath) {
    string path = filePath;
    if (path.back() != '/') {
        path += "/";
    }
    string pathLWR = path;
    string pathLWB = path;
    pathLWR += "backup.lwr";
    pathLWB += "backup.lwb";
    int runResult = 0;
    runResult += buildReaderPool(pathLWR);
    runResult += buildBookPool(pathLWB);
    return runResult;
}

int Library::buildBookPool(string filePath) {
    ifstream fin(filePath);
    if (!fin) return 1;
    string reading;
    string buffer;
    string lastReading;
    double price;
    int num = 0;
    unsigned rid;
    BookNode* p;
    fin >> buffer;                          //Read the No.
    reading = buffer;
    fin >> buffer;                          //Read name into the buffer.
    while (reading != buffer) {
        ISBN tmpISBN;
        fin >> reading;                     //Read the next string.
        while (!(tmpISBN << reading)) {     //If this string is not an ISBN code.
            buffer += " ";                  //Add this string to the name.
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
            buffer += " ";                  //Add this string to the author.
            buffer += reading;
            fin >> reading;                 //Read another string.
        }
        bookPool->book->date = tmpDate;     //If this string is a Date code.
        bookPool->book->author = buffer;    //Input the author and the date to the new node.
        fin >> price;                       //Read the price.
        bookPool->book->inputPrice(price);  //Input the price to the new node.
        fin >> num;
        bookPool->book->quantity = num;     //Input the quantity of the new node.
        fin >> num;
        for (int i = 0; i<num; i++) {       //Input the readers.
            fin >> reading;
            rid = (unsigned)stoul(reading);
            bookPool->book->borrowBook(rid);
        }
        bookNumber++;
        tmpDate.year = 0;
        tmpISBN.group1 = 0;
        lastReading = reading;
        fin >> buffer;                       //Read the No.
        reading = buffer;
        fin >> buffer;                       //Read name into the buffer.
    }
    fin.close();
    return 0;
}

int Library::buildReaderPool(string filePath) {
    ifstream fin(filePath);
    if(!fin) return 2;
    string reading;
    string buffer;
    unsigned ridIn;
    int tmpCount;
    int borrowedIn;
    ReaderNode* p;
    fin >> buffer;
    reading = buffer;
    fin >> buffer;
    while (reading != buffer) {
        ridIn = (unsigned)stoul(reading);
        p = readerPool;
        readerPool = new ReaderNode(ridIn);
        readerNumber++;
        if(ridCount <= ridIn)
            ridCount = ridIn+1;
        readerPool->nextReader = p;
        readerPool->reader->name = buffer;
        fin >> reading;
        readerPool->reader->level = stoi(reading);
        fin >> reading;
        readerPool->reader->email = reading;
        fin >> borrowedIn;
        fin >> tmpCount;
        ISBN* booksBorrowed = new ISBN[tmpCount];
        Date* booksDate = new Date[tmpCount];
        bool* booksRenew = new bool[tmpCount];
        for (int i=0; i<tmpCount; i++) {
            fin >> reading;
            booksBorrowed[i] << reading;
            fin >> reading;
            booksDate[i] << reading;
            fin >> booksRenew[i];
        }
        readerPool->reader->importData(booksBorrowed, booksDate, booksRenew, tmpCount, borrowedIn);
        delete [] booksRenew;
        delete [] booksDate;
        delete [] booksBorrowed;
        fin >> buffer;
        reading = buffer;
        fin >> buffer;
    }
    return 0;
}