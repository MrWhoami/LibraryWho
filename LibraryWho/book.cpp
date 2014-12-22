//
//  library.cpp
//  LibraryWho
//
//  Created by Whoami on 14/12/14.
//  Copyright (c) 2014年 Jiyuan Liu.
//

#include "book.h"

BorrowNode::BorrowNode() {
    rid = 0;
    nextReader = NULL;
}

Book::Book(ISBN isbnIn) {
    isbn.group1 = isbnIn.group1;
    isbn.group2 = isbnIn.group2;
    isbn.group3 = isbnIn.group3;
    isbn.group4 = isbnIn.group4;
    isbn.group5 = isbnIn.group5;
    date.year = 2000;
    date.month = 1;
    date.day = 1;
    price = 0;
    quantity = 0;
    readers = NULL;
}

Book::~Book() {
    BorrowNode *p = readers;
    while (readers != NULL) {
        p = readers;
        readers = readers->nextReader;
        delete p;
    }
}

void Book::inputPrice(double priceIn) {
    if (priceIn < 0) {
        price = 0;
        return;
    }
    price = (unsigned)(priceIn * 100);
}

double Book::outputPrice() {
    return ((double)price)/100;
}

/*
bool Book::readerReturn(unsigned rRid) {
    BorrowNode* p = readers;
    BorrowNode* pre = NULL;
    time_t rawtime;
    tm* now;
    time(&rawtime);
    now = localtime(&rawtime);
    while (p != NULL) {
        if (p->rid == rRid) {
            Date expect = p->returnDate();
            if (expect.year < now->tm_year) {
                return 1;
            }
            else if (expect.month < now->tm_mon+1){
                return 1;
            }
            else if (expect.day < now->tm_mday) {
                return 1;
            }
            else {
                if (pre == NULL) {
                    readers = p->nextReader;
                } else {
                    pre->nextReader = p->nextReader;
                }
                delete p;
                return 1;
            }
        } else {
            pre = p;
            p = p->nextReader;
        }
    }
    return 0;
}
 */

ISBN Book::getISBN() {
    return isbn;
}

int Book::getReaderNum() {
    BorrowNode *p = readers;
    int num = 0;
    while (p != NULL) {
        num++;
        p = p->nextReader;
    }
    return num;
}

int Book::getTotal() {
    return getReaderNum()+quantity;
}

int Book::getReaders(unsigned* &rid) {
    BorrowNode *p = readers;
    for (int i=0; i<getReaderNum(); i++) {
        rid[i] = p->rid;
        p = p->nextReader;
    }
    return getReaderNum();
}

int Book::borrowBook(unsigned rid) {
    if (quantity < 1) {
        return 1;
    }
    BorrowNode* p = readers;
    while (p != NULL) {
        if (p->rid == rid) {
            return 2;
        }
        p = p->nextReader;
    }
    p = readers;
    readers = new BorrowNode;
    readers->rid = rid;
    readers->nextReader = p;
    quantity--;
    return 0;
}

int Book::returnBook(unsigned rid) {
    BorrowNode* p = readers;
    BorrowNode* pre = NULL;
    while (p != NULL) {
        if (p->rid == rid) {
            if (pre == NULL) {
                readers = p->nextReader;
            } else {
                pre->nextReader = p->nextReader;
            }
            delete p;
            quantity++;
            return 0;
        } else {
            pre = p;
            p = p->nextReader;
        }
    }
    return 1;
}