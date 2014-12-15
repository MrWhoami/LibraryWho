//
//  library.cpp
//  Library
//
//  Created by Whoami on 14/12/14.
//  Copyright (c) 2014年 Whoami.
//

#include "book.h"

BorrowNode::BorrowNode(){
    borrowDate.year = 2000;
    borrowDate.month = 1;
    borrowDate.day = 1;
    renew = 0;
    rid = 0;
    nextReader = NULL;
}

Date BorrowNode::returnDate(){
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

Book::Book(ISBN isbnIn){
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

void Book::inputPrice(double priceIn) {
    if (priceIn < 0) {
        price = 0;
        return;
    }
    price = (unsigned)(priceIn * 100);
}

void Book::inputISBN(string isbnIn) {
    sscanf(isbnIn.c_str(), "%d-%d-%d-%d-%d", &isbn.group1, &isbn.group2, &isbn.group3, &isbn.group4, &isbn.group5);
}

void Book::ruleBreaker(Queue<unsigned> &breakers){
    BorrowNode* current = readers;
    time_t rawtime;
    tm* now;
    time(&rawtime);
    now = localtime(&rawtime);
    while (current != NULL) {
        Date expect = current->returnDate();
        if (expect.year > now->tm_year) {
            current = current->nextReader;
            continue;
        }
        else if (expect.month > now->tm_mon+1){
            current = current->nextReader;
            continue;
        }
        else if (expect.day >= now->tm_mday) {
            current = current->nextReader;
            continue;
        }
        else {
            breakers.enQueue(current->rid);
        }
        current = current->nextReader;
    }
}

double Book::outputPrice(){
    return ((double)price)/100;
}

int Book::readerReturn(unsigned rRid) {
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
                return 0;
            }
        } else {
            pre = p;
            p = p->nextReader;
        }
    }
    return 2;
}