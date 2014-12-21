//
//  main.cpp
//  Library
//
//  Created by Whoami on 14/12/14.
//  Copyright (c) 2014年 Jiyuan Liu.
//

#include <fstream>
#include <iostream>
#include "common.h"
#include "library.h"

Library library;
bool test;

void printHelp(){
    cout << "OPTION FUNCTION" << endl;
    cout << " ?(H)  Viewing this page." << endl;
    cout << " Q     Quit this program." << endl;
    cout << " A     Add books to this library through a file." << endl;
    cout << " E     Export the library books into a file." <<  endl;
    cout << " I     Search the book with an ISBN code." << endl;
    cout << " B     Search the book with the name." << endl;
    cout << " P     Print the information of the current book." << endl;
    cout << " T     Test if the file can be read correctly. " << endl;
}

void cmd_A() {
    if (!test) {
        cout << "You haven't test the data file yet. Do you want to test it before use? (0/1)" << endl;
        cin >> test;
        if (test) {
            test = 0;
            return;
        }
    }
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
    cout << "Please input the path if the file to be test: " << endl;
    string path;
    cin >> path;
    ifstream fin(path);
    string a;
    for (int i = 0; i<20; i++) {
        fin >> a;
        cout << a << endl;
    }
    fin.close();
    test = 1;
}

void cmd_I(){
    library.ISBN_search();
    library.printBookInfo();
}
void cmd_B(){
    library.BOOKNAME_search();
    library.printBookInfo();
}

void cmd_P(){
    library.printBookInfo();
}

int main(int argc, const char * argv[]) {
    cout << "============ LibraryWho ============" << endl;
    char option = '~';
    test = 0;
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
            case 'P':
                cmd_P();
                option = '~';
                break;
            case 'B':
                cmd_B();
                option = '~';
                break;
                
            default:
                cout << "Invalid option: " << option << endl;
                option = '~';
                break;
        }
    }
}
