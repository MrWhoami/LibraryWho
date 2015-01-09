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

/*
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
    cout << " H     Renew the book's return date." << endl;
}
*/
void printHelpNew(){
    cout << "OPTION    FUNCTION" << endl;
    cout << " ?(HELP)  Viewing this page." << endl;                                //1
    cout << " QUIT     Quit this program." << endl;                                //-1
    cout << " AB       Add books to this library through a file." << endl;         //2
    cout << " EX       Export the library books into a file." <<  endl;            //3
    cout << " ISBN     Search the book with an ISBN code." << endl;                //4
    cout << " BNAM     Search the book with the name." << endl;                    //5
    cout << " INFO     Print the information of the current book." << endl;        //6
    cout << " TEST     Test if the file can be read correctly. " << endl;          //7
    cout << " AR       Add readers by command line." << endl;                      //8
    cout << " BKUP     Export all the library information into a folder." << endl; //9
    cout << " RESM     Import all the library information from a folder." << endl; //10
    cout << " BORW     The reader now want to borrow the book now." << endl;       //11
    cout << " RETN     The reader now want to return the book now." << endl;       //12
    cout << " AUTH     Search the book with the author's name." << endl;           //13
    cout << " RID      Search the reader with the RID." << endl;                   //14
    cout << " RNAM     Search the reader with the name." << endl;                  //15
    cout << " EMAIL    Search the reader with the e-mail." << endl;                //16
    cout << " RPTNAM   Search the book with part of its name. " << endl;           //17
    cout << " RENEW    Renew the book's return date." << endl;                     //18
    cout << " LBINFO   Print the information of the library." << endl;             //19
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
        int returnNum = library.returnBook();
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

void cmd_H() {
    cout << library.readerNow->name << " will renew " << library.bookNow->name <<" (0/1)?" << endl;
    cout << "[LibraryWho]: ";
    bool judge = 0;
    cin >> judge;
    if (judge) {
        int returnNum = library.renewBook();
        switch (returnNum) {
            case 0:
                cout << "Success." << endl;
                break;
            case 1:
                cout << "The reader hasn't borrowed the book yet." << endl;
                break;
            case 2:
                cout << "The reader has renewed its return date." << endl;
                break;
            case 4:
                cout << "The reader has broken the rule." << endl;
                break;
                
            default:
                cout << "Unknown error." << endl;
                break;
        }
    }
}

void cmd_19() {
    cout << "Book number: " << library.getBookNumber() << endl;
    cout << "Reader number: " << library.getReaderNumber() << endl;
}

int optionSelect(string optionIn) {
    if (optionIn == "QUIT")
        return -1;
    else if (optionIn == "HELP")
        return 1;
    else if (optionIn == "?")
        return 1;
    else if (optionIn == "AB")
        return 2;
    else if (optionIn == "EX")
        return 3;
    else if (optionIn == "ISBN")
        return 4;
    else if (optionIn == "BNAM")
        return 5;
    else if (optionIn == "INFO")
        return 6;
    else if (optionIn == "TEST")
        return 7;
    else if (optionIn == "AR")
        return 8;
    else if (optionIn == "BKUP")
        return 9;
    else if (optionIn == "RESM")
        return 10;
    else if (optionIn == "BORM")
        return 11;
    else if (optionIn == "RETN")
        return 12;
    else if (optionIn == "AUTH")
        return 13;
    else if (optionIn == "RID")
        return 14;
    else if (optionIn == "RNAM")
        return 15;
    else if (optionIn == "EMAIL")
        return 16;
    else if (optionIn == "RPTNAM")
        return 17;
    else if (optionIn == "RENEW")
        return 18;
    else if (optionIn == "LBINFO")
        return 19;
    else
        return 0;
}

int main(int argc, const char * argv[]) {
    cout << "============ LibraryWho ============" << endl;
    //char option = '~';
    string optionIn;
    int option = 0;
    test = 0;
    bool readBackup = 0;
    readBackup = cmd_I();
    while (option != -1) {
        cout << endl;
        cout << "Please input an option (? for help): " << endl;
        cout << "[LibraryWho]: ";
        cin >> optionIn;
        option = optionSelect(optionIn);
        switch (option) {
            case -1:
                cout << "Would you like to backup your data ?(0/1)" << endl;
                cout << "[LibraryWho]: ";
                cin >> test;
                if (test) {
                    cmd_E();
                }
                return 0;
                break;
            case 1:
                printHelpNew();
                break;
            case 2:
                cmd_A();
                break;
            case 3:
                cmd_F();
                break;
            case 4:
                cmd_C();
                break;
            case 5:
                cmd_B();
                break;
            case 6:
                cmd_P();
                break;
            case 7:
                cmd_T();
                break;
            case 8:
                cmd_R();
                break;
            case 9:
                cmd_E();
                break;
            case 10:
                if (readBackup) {
                    cout << "You have already input the backup data." << endl;
                } else {
                    readBackup = cmd_I();
                }
                break;
            case 11:
                cmd_N();
                break;
            case 12:
                cmd_O();
                break;
            case 13:
                cmd_W();
                break;
            case 14:
                cmd_U();
                break;
            case 16:
                cmd_M();
                break;
            case 15:
                cmd_D();
                break;
            case 17:
                cmd_G();
                break;
            case 18:
                cmd_H();
                break;
            case 19:
                cmd_19();
                break;

                
            default:
                cout << "Invalid command: " << optionIn << endl;
                break;
        }
        option = 0;
        optionIn = "No option.";
        /*
        switch (option) {
            case 'Q':
                cout << "Would you like to backup your data ?(0/1)" << endl;
                cout << "[LibraryWho]: ";
                cin >> test;
                if (test) {
                    cmd_E();
                }
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
                break;
            case 'U':
                cmd_U();
                option = '~';
                break;
            case 'M':
                cmd_M();
                option = '~';
                break;
            case 'D':
                cmd_D();
                option = '~';
                break;
            case 'G':
                cmd_G();
                option = '~';
                break;
                
            default:
                cout << "Invalid option: " << option << endl;
                option = '~';
                break;
        }
        */
    }
}
