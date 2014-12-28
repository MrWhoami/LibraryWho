//
//  HashTable.cpp
//  LibraryWho
//
//  Created by Jiyuan Liu on 14/12/28.
//  Copyright (c) 2014年 Jiyuan Liu. All rights reserved.
//

#include "HashTable.h"

HashTableBook::HashTableBook(int d) {
    divisor = d;
    head = new ChainNode<BookNode*>*[divisor];
    assert(head != NULL);
}

HashTableBook::~HashTableBook() {
    delete [] head;
}

ChainNode<BookNode*>* HashTableBook::findPosition(ISBN isbnIn) {
    unsigned long long isbnULL;
    isbnIn >> isbnULL;
    int group = (int)(isbnULL%(unsigned long long)divisor);
    return head[group];
}

bool HashTableBook::searchBook(ISBN isbnIn) {
    ChainNode<BookNode*>* p = findPosition(isbnIn);
    while (p != NULL) {
        if (p->data->book->getISBN() == isbnIn) {
            return 1;
        }
    }
    return 0;
}

bool HashTableBook::searchBook(ISBN isbnIn, BookNode** target) {
    ChainNode<BookNode*>* p = findPosition(isbnIn);
    while (p != NULL) {
        if (p->data->book->getISBN() == isbnIn) {
            *target = p->data;
            return 1;
        }
    }
    return 0;
}

bool HashTableBook::insertBook(BookNode* target) {
    if (searchBook(target->book->getISBN())) {
        return 0;
    }
    ChainNode<BookNode*>* p = findPosition(target->book->getISBN());
    if (p == NULL) {
        unsigned long long isbnULL;
        target->book->getISBN() >> isbnULL;
        int group = (int)(isbnULL%(unsigned long long)divisor);
        head[group] = new ChainNode<BookNode*>;
        head[group]->data = target;
        return 1;
    }
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = new ChainNode<BookNode*>;
    p->next->data = target;
    return 1;
}

bool HashTableBook::removeBook(BookNode* target) {
    BookNode *p = NULL;
    if (!searchBook(target->book->getISBN(), &p)) {
        return 0;
    } else {
        unsigned long long isbnULL;
        target->book->getISBN() >> isbnULL;
        int group = (int)(isbnULL%(unsigned long long)divisor);
        if (head[group]->data == p) {
            ChainNode<BookNode*>* tmp = head[group];
            head[group] = tmp->next;
            delete tmp;
        }
        else {
            ChainNode<BookNode*>* tmp = head[group];
            ChainNode<BookNode*>* pre = NULL;
            while (tmp->data != p) {
                pre = tmp;
                tmp = tmp->next;
            }
            pre->next = tmp->next;
            delete tmp;
        }
        return 1;
    }
}