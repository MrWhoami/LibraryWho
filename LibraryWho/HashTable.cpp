//
//  HashTable.cpp
//  LibraryWho
//
//  Created by Jiyuan Liu on 14/12/28.
//  Copyright (c) 2014年 Jiyuan Liu. All rights reserved.
//

#include "HashTable.h"
#include <cstdio>

HashTableBook::HashTableBook(int d) {
    divisor = d;
    head = new ChainNode<BookNode*>*[divisor];
    for (int i=0; i<(int)MAX_SIZE; i++) {
        head[i] = NULL;
    }
    assert(head != NULL);
}

HashTableBook::~HashTableBook() {       //May leave some rubbish.
    delete [] head;
}

int HashTableBook::findPosition(ISBN isbnIn) {
    unsigned long long isbnULL;
    isbnIn >> isbnULL;
    int group = (int)(isbnULL%(unsigned long long)divisor);
    return group;
}

bool HashTableBook::searchBook(ISBN &isbnIn) {
    int group = findPosition(isbnIn);
    //Test
    printf("group: %d\n", group);
    //
    ChainNode<BookNode*>* p = head[group];
    ISBN tmp;
    while (p != NULL) {
        tmp = p->data->book->getISBN();
        if (tmp == isbnIn) {
            //Test
            printf("Return 1\n");
            return 1;
        }
        p = p->next;
    }
    //Test
    printf("Return 0\n");
    return 0;
}

bool HashTableBook::searchBook(ISBN &isbnIn, BookNode** target) {
    int group = findPosition(isbnIn);
    ChainNode<BookNode*>* p = head[group];
    //Test
    printf("group: %d\n", group);
    //
    while (p != NULL) {
        //Test
        printf("date %d %d\n", p->data->book->date.year ,p->data->book->date.month);
        if (p->data->book->getISBN() == isbnIn) {
            *target = p->data;
            return 1;
        }
        p = p->next;
    }
    //Test
    printf("Return 0\n");
    return 0;
}

bool HashTableBook::insertBook(BookNode* target) {
    ISBN tmp = target->book->getISBN();
    if (searchBook(tmp)) {
        return 0;
    }
    int group = findPosition(target->book->getISBN());
    if (head[group] == NULL) {
        head[group] = new ChainNode<BookNode*>;
        head[group]->data = target;
        head[group]->next = NULL;
        return 1;
    }
    ChainNode<BookNode*>* p = head[group];
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = new ChainNode<BookNode*>;
    p->next->data = target;
    p->next = NULL;
    return 1;
}

bool HashTableBook::removeBook(BookNode* target) {
    BookNode *p = NULL;
    ISBN tmpISBN = target->book->getISBN();
    if (!searchBook(tmpISBN, &p)) {
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