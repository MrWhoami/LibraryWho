//
//  common.h
//  LibraryWho
//
//  Created by Whoami on 14/12/15.
//  Copyright (c) 2014年 Jiyuan Liu.
//

#ifndef LibraryWho_common_h
#define LibraryWho_common_h

#include <string>
using namespace std;
#include <assert.h>

const string DEFAULT_PATH = "/Users/apple/Documents/LibraryWho/";
const unsigned MAX_SIZE = 10007;

class Date {
public:
    short year;
    short month;
    short day;
    bool operator == (const Date& x);
    bool operator != (const Date& x);
    bool operator << (const string dataIn);
};

class ISBN {
public:
    /*
    unsigned group1;
    unsigned group2;
    unsigned group3;
    unsigned group4;
    unsigned group5;
     */
    string group1s;
    string group2s;
    string group3s;
    string group4s;
    string group5s;
    bool operator == (ISBN &x);
    bool operator != (ISBN &x);
    void operator >> (unsigned long long &isbnInt);
    bool operator << (const string isbnIn);
    void operator = (ISBN &x);
    void operator = (ISBN x);
};

#endif