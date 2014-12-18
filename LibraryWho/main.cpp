//
//  main.cpp
//  Library
//
//  Created by Whoami on 14/12/14.
//  Copyright (c) 2014年 Whoami.
//

#include <fstream>
#include <iostream>
#include "common.h"
#include "library.h"

Library library;

void printHelp(){
    cout << "OPTION FUNCTION" << endl;
    cout << " ?(H)  Viewing this page." << endl;
    cout << " Q     Quit this program." << endl;
    cout << " A     Add books to this library through a file." << endl;
    cout << " E     Export the library books into a file." <<  endl;
    cout << " I     Search the book with an ISBN code." << endl;
}

void cmd_A() {
    cout << "Please input the path of the file: " << endl;
    string path;
    cin >> path;
    int result;
    result = library.buildALibrary(path);
    switch (result) {
        case 0:
            cout << "Success." << endl;
            break;
        case -1:
            cout << "Wrong path." << endl;
            break;
            
        default:
            cout << "Unknown cases." << endl;
            break;
    }
}

void cmd_E() {
    cout << "Please input the path of the file: " << endl;
    string path;
    cin >> path;
    int result;
    result = library.printAllBooks(path);
    switch (result) {
        case 0:
            cout << "Success." << endl;
            break;
        case -1:
            cout << "Wrong path." << endl;
            break;
            
        default:
            cout << "Unknown cases." << endl;
            break;
    }
}

void cmd_T(){
    string path;
    cin >> path;
    ifstream fin(path);
    string a;
    for (int i = 0; i<20; i++) {
        fin >> a;
        cout << a << endl;
    }
    fin.close();
}

void cmd_I(){
    Book* tmp = library.ISBN_search();
    if (tmp != NULL) {
        cout << tmp->name << endl;
        cout << tmp->author << endl;
        cout << tmp->date.year << ' ' << tmp->date.month << ' ' <<  tmp->date.day << endl;
        cout << tmp->outputPrice() << endl;
    }
}

int main(int argc, const char * argv[]) {
    cout << "============ LibraryWho ============" << endl;
    char option = '~';
    Library library;
    while (option != 0) {
        cout << endl;
        cout << "Please input an option (? for help): " << endl;
        cin >> option;
        switch (option) {
            case 'Q':
            case 'q':
                return 0;
                break;
            case '?':
            case 'h':
            case 'H':
                printHelp();
                option = '~';
                break;
            case 'A':
                cmd_A();
                option = '~';
                break;
            case 'E':
                cmd_E();
                option = '~';
                break;
            case 'T':
                cmd_T();
                option = '~';
                break;
            case 'I':
                cmd_I();
                option = '~';
                break;
                
            default:
                break;
        }
    }
}
