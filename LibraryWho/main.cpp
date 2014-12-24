//
//  main.cpp
//  LibraryWho
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
    cout << " F     Export the library books into a file." <<  endl;
    cout << " C     Search the book with an ISBN code." << endl;
    cout << " B     Search the book with the name." << endl;
    cout << " P     Print the information of the current book." << endl;
    cout << " T     Test if the file can be read correctly. " << endl;
    cout << " R     Add readers by command line." << endl;
    cout << " E     Export all the library information into a folder." << endl;
    cout << " I     Import all the library information from a folder." << endl;
    cout << " N     The reader now want to borrow the book now." << endl;
    cout << " O     The reader now want to return the book now." << endl;
    cout << " W     Search the book with the author's name." << endl;
    cout << " U     Search the reader with the RID." << endl;
    cout << " D     Search the reader with the name." << endl;
    cout << " M     Search the reader with the e-mail." << endl;
    cout << " G     Search the book with part of its name. " << endl;
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

void cmd_F() {
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

void cmd_C() {
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

void cmd_R() {
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
    switch (runResult) {
        case 0:
            cout << "Exported successfully." << endl;
            break;
        case 1:
            cout << "Fail to export *.lwb." << endl;
            break;
        case 3:
            cout << "Fail to export *.lwb." << endl;
        case 2:
            cout << "Fail to export *.lwr." << endl;
            break;
            
        default:
            cout << "Unknown cases while exporting backups." << endl;
            break;
    }
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
        case 0:
            cout << "No operation." << endl;
            return 0;
            break;
        case 1:
            cout << "Using the default path. " << endl;
            path = DEFAULT_PATH;
            break;
        case 2:
            cout << "Please input the path. " << endl;
            cin >> path;
            break;
            
        default:
            cout << "Invalid option. No operation will be taken. If you want to import the backup files later, just use the option 'I'" << endl;
            return 0;
            break;
    }
    runResult = library.buildALibrary(path);
    switch (runResult) {
        case 0:
            cout << "Imported successfully." << endl;
            return 1;
            break;
        case 1:
            cout << "Fail to import *.lwb." << endl;
            break;
        case 3:
            cout << "Fail to import *.lwb." << endl;
        case 2:
            cout << "Fail to import *.lwr." << endl;
            break;
            
        default:
            cout << "Unknown cases while importing backups." << endl;
            break;
    }
    return 0;
}

void cmd_N() {
    cout << library.readerNow->name << " will borrow " << library.bookNow->name <<" (0/1)?" << endl;
    cout << "[LibraryWho]: ";
    bool judge = 0;
    cin >> judge;
    if (judge) {
        int returnNum = library.borrowBook();
        if (returnNum == 0) {
            cout << "Borrowed successfully. " << endl;
            return;
        }
        if(returnNum&1)
            cout << "No book selected." << endl;
        returnNum = returnNum >> 1;
        if (returnNum&1)
            cout << "No reader selected." << endl;
        returnNum = returnNum >> 1;
        if (returnNum&1)
            cout << "No book left." << endl;
        returnNum = returnNum >> 1;
        if (returnNum&1)
            cout << "The reader has already borrowed the book." << endl;
        returnNum = returnNum >> 1;
        if (returnNum&1)
            cout << "The reader has reach the borrow limit." << endl;
        returnNum = returnNum >> 1;
        if (returnNum&1)
            cout << "The reader has already borrowed the book." << endl;
    } else {
        cout << "Cancaled." << endl;
    }
}

void cmd_O() {
    cout << library.readerNow->name << " will return " << library.bookNow->name <<" (0/1)?" << endl;
    cout << "[LibraryWho]: ";
    bool judge = 0;
    cin >> judge;
    if (judge) {
        int returnNum = library.borrowBook();
        if (returnNum == 0) {
            cout << "Returned successfully. " << endl;
            return;
        }
        if(returnNum&1)
            cout << "No book selected." << endl;
        returnNum = returnNum >> 1;
        if (returnNum&1)
            cout << "No reader selected." << endl;
        returnNum = returnNum >> 1;
        if (returnNum&1)
            cout << "No book borrowed." << endl;
        returnNum = returnNum >> 1;
        if (returnNum&1)
            cout << "The reader hasn't borrowed the book." << endl;
        returnNum = returnNum >> 1;
        if (returnNum&1)
            cout << "The reader has broken the time limit." << endl;
    } else {
        cout << "Cancaled." << endl;
    }
}

void cmd_W() {
    library.AUTHORpart_search();
}

void cmd_U() {
    library.RID_search();
}

void cmd_D() {
    library.READERNAME_search();
}

void cmd_M() {
    library.EMAIL_search();
}

void cmd_G() {
    library.BOOKNAMEpart_search();
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
                option = 0;
                return 0;
                break;
            case '?':
            case 'H':
                printHelp();
                option = '~';
                break;
            case 'A':
                cmd_A();
                option = '~';
                break;
            case 'F':
                cmd_F();
                option = '~';
                break;
            case 'T':
                cmd_T();
                option = '~';
                break;
            case 'C':
                cmd_C();
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
            case 'R':
                cmd_R();
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
            case 'N':
                cmd_N();
                option = '~';
                break;
            case 'O':
                cmd_O();
                option = '~';
                break;
            case 'W':
                cmd_W();
                option = '~';
            case 'U':
                cmd_U();
                option = '~';
            case 'M':
                cmd_M();
                option = '~';
            case 'D':
                cmd_D();
                option = '~';
                break;
            case 'G':
                cmd_G();
                option = '~';
                
            default:
                cout << "Invalid option: " << option << endl;
                option = '~';
                break;
        }
    }
}
