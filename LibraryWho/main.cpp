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
    cout << " e     Export the library books into a file." <<  endl;
    cout << " i     Search the book with an ISBN code." << endl;
    cout << " B     Search the book with the name." << endl;
    cout << " P     Print the information of the current book." << endl;
    cout << " T     Test if the file can be read correctly. " << endl;
    cout << " r     Add readers by command line." << endl;
    cout << " E     Export all the library infomation into a folder." << endl;
}

void cmd_A() {
    if (!test) {
        cout << "You haven't test the data file yet. Do you want to test it before use? (0/1)" << endl;
        cout << "[LibraryWho]: ";
        cin >> test;
        if (test) {
            test = 0;
            return;
        }
    }
    int num = 1;
    cout << "Please input the quantity of each book about to input: " << endl;
    cout << "[LibraryWho]: ";
    cin >> num;
    if (num < 0) {
        cout << "Invalid number. Set the number 0." << endl;
        num = 0;
    }
    cout << "Please input the path of the file: " << endl;
    cout << "[LibraryWho]: ";
    string path;
    cin >> path;
    int result;
    result = library.importBooks(path, num);
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

void cmd_e() {
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

void cmd_T() {
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

void cmd_i() {
    library.ISBN_search();
    library.printBookInfo();
}

void cmd_B() {
    library.BOOKNAME_search();
    library.printBookInfo();
}

void cmd_P() {
    library.printBookInfo();
}

void cmd_r() {
    int num = 0;
    int levelIn = 0;
    cout << "Please input the number of readers to be input: ";
    cin >> num;
    cout << "And their level: ";
    cin >> levelIn;
    switch (library.addReaders(num, levelIn)) {
        case 0:
            cout << "Added all the readers successfully." << endl;
            break;
        case 1:
            cout << "Invalid reader number." << endl;
            break;
        case 2:
            cout << "Invalid level. " << endl;
            break;
        case 3:
            cout << "Invalid reader number and level." << endl;
            break;
            
        default:
            cout << "Unknown error." << endl;
            break;
    }
}

void cmd_E() {
    cout << "Use default path(0/1) ?" << endl;
    bool defPath = 1;
    string path;
    int runResult = -1;
    cout << "[LibraryWho]: ";
    cin >> defPath;
    if (defPath){
        path = DEFAULT_PATH;
    } else {
        cout << "Input the path of the target folder: " << endl;
        cout << "[LibraryWho]: ";
        cin >> path;
    }
    runResult = library.exportTheLibrary(path);
    //Switch runResult.
}

bool cmd_I() {
    cout << "Import the back up date ?" << endl;
    cout << "0. No.   1. Default path.   2. Other path." << endl;
    cout << "[LibraryWho]: ";
    int option = 0;
    int runResult = 0;
    string path;
    cin >> option;
    switch (option) {
        case '0':
            cout << "No operation." << endl;
            break;
        case '1':
            cout << "Using the default path. " << endl;
            path = DEFAULT_PATH;
            break;
        case '2':
            cout << "Please input the path. " << endl;
            cin >> path;
            break;
            
        default:
            cout << "Invalid option. No operation will be taken. If you want to import the backup files later, just use the option 'I'" << endl;;
            break;
    }
    runResult = library.buildALibrary(path);
    //Switch runResult;
    return 0;
}

int main(int argc, const char * argv[]) {
    cout << "============ LibraryWho ============" << endl;
    char option = '~';
    test = 0;
    bool readBackup = 0;
    readBackup = cmd_I();
    while (option != 0) {
        cout << endl;
        cout << "Please input an option (? for help): " << endl;
        cout << "[LibraryWho]: ";
        cin >> option;
        switch (option) {
            case 'Q':
            case 'q':
                option = 0;
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
            case 'e':
                cmd_e();
                option = '~';
                break;
            case 'T':
                cmd_T();
                option = '~';
                break;
            case 'i':
                cmd_i();
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
            case 'r':
                cmd_r();
                option = '~';
                break;
            case 'E':
                cmd_E();
                option = '~';
                break;
            case 'I':
                if (readBackup) {
                    cout << "You have already input the backup data." << endl;
                } else {
                    readBackup = cmd_I();
                }
                option = '~';
                break;
                
            default:
                cout << "Invalid option: " << option << endl;
                option = '~';
                break;
        }
    }
}
