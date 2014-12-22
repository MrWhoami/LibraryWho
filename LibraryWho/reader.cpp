//
//  reader.cpp
//  LibraryWho
//
//  Created by Whoami on 14/12/15.
//  Copyright (c) 2014年 Jiyuan Liu.
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

bool Reader::borrowNew(ISBN newBook){
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
    borrowed++;
    return 1;
}

int Reader::returnOld(ISBN oldBook) {
/*
    if (bookBorrowed == NULL) {
        return 0;
    }
    BookBorrowed *p = bookBorrowed;
    if (p->theBook == oldBook) {
        bookBorrowed = p->nextBook;
        delete p;
    } else {
        while (p->nextBook != NULL || p->nextBook->theBook != oldBook) {
            p = p->nextBook;
        }
        if (p->nextBook == NULL) {
            return 0;
        }
        BookBorrowed *tod = p->nextBook;
        p->nextBook = tod->nextBook;
        delete tod;
    }
    return 1;
 */
    BookBorrowed *pre = NULL;
    BookBorrowed *p = bookBorrowed;
    while (p!=NULL && p->theBook!=oldBook) {
        pre = p;
        p = p->nextBook;
    }
    if (p == NULL) {
        return 0;
    } else {
        int returnNum = 1;
        time_t rawtime;
        tm* now;
        time(&rawtime);
        now = localtime(&rawtime);
        Date expect = p->returnDate();
        if (expect.year < now->tm_year) {
            returnNum = 2;
        }
        else if (expect.month < now->tm_mon+1){
            returnNum = 2;
        }
        else if (expect.day < now->tm_mday) {
            returnNum = 2;
        }
        else {
            returnNum = 1;
        }
        if (pre == NULL) {
            bookBorrowed = p->nextBook;
        } else {
            pre->nextBook = p->nextBook;
        }
        delete p;
        return returnNum;
    }
}

int Reader::getBook(ISBN* &borrowedList) {
    BookBorrowed *p = bookBorrowed;
    int i = 0;
    while (p != NULL) {
        borrowedList[i] = p->theBook;
        i++;
    }
    return i;
}

int Reader::getData(Date* &borrowedList) {
    BookBorrowed* p = bookBorrowed;
    int i = 0;
    while (p != NULL) {
        borrowedList[i] = p->borrowDate;
        i++;
    }
    return i;
}

int Reader::getRenew(bool* &borrowedList) {
    BookBorrowed* p = bookBorrowed;
    int i = 0;
    while (p != NULL) {
        borrowedList[i] = p->renew;
        i++;
    }
    return i;
}

Date BookBorrowed::returnDate(){
    Date returnDay = borrowDate;
    returnDay.day += 30;
    switch (borrowDate.month) {
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
            if (returnDay.day > 31) {
                returnDay.day -= 31;
                returnDay.month += 1;
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            if (returnDay.day > 30) {
                returnDay.day -= 30;
                returnDay.month += 1;
            }
            break;
        case 1:
            if (returnDay.day > 31) {
                returnDay.day -= 31;
                returnDay.month += 1;
            }
        case 2:
            short feb;
            if (returnDay.year%4 == 0) {
                if (returnDay.year%100 == 0) {
                    if (returnDay.year%400 == 0) {
                        feb = 29;
                    } else {
                        feb =28;
                    }
                } else {
                    feb = 29;
                }
            } else {
                feb = 28;
            }
            if (returnDay.day > feb) {
                returnDay.day -= feb;
                returnDay.month += 1;
            }
            break;
        case 12:
            if (returnDay.day > 31) {
                returnDay.day -= 31;
                returnDay.month = 1;
                returnDay.year += 1;
            }
            break;
            
        default:
            returnDay.year = 2000;
            returnDay.month = 1;
            returnDay.day = 1;
            break;
    }
    if (renew) {
        returnDay.day += 30;
        switch (borrowDate.month) {
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
                if (returnDay.day > 31) {
                    returnDay.day -= 31;
                    returnDay.month += 1;
                }
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                if (returnDay.day > 30) {
                    returnDay.day -= 30;
                    returnDay.month += 1;
                }
                break;
            case 1:
                if (returnDay.day > 31) {
                    returnDay.day -= 31;
                    returnDay.month += 1;
                }
            case 2:
                short feb;
                if (returnDay.year%4 == 0) {
                    if (returnDay.year%100 == 0) {
                        if (returnDay.year%400 == 0) {
                            feb = 29;
                        } else {
                            feb =28;
                        }
                    } else {
                        feb = 29;
                    }
                } else {
                    feb = 28;
                }
                if (returnDay.day > feb) {
                    returnDay.day -= feb;
                    returnDay.month += 1;
                }
                break;
            case 12:
                if (returnDay.day > 31) {
                    returnDay.day -= 31;
                    returnDay.month = 1;
                    returnDay.year += 1;
                }
                break;
                
            default:
                returnDay.year = 2000;
                returnDay.month = 1;
                returnDay.day = 1;
                break;
        }
    }
    return returnDay;
}

int Reader::getBorrowed(){
    return borrowed;
}