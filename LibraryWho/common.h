//
//  common.h
//  LibraryWho
//
//  Created by Whoami on 14/12/15.
//  Copyright (c) 2014年 Whoami.
//

#ifndef LibraryWho_common_h
#define LibraryWho_common_h

#include <string>
using namespace std;

struct Date {
    short year;
    short month;
    short day;
    bool operator ==(const Date& x) {
        bool equal = 1;
        equal = (this->year==x.year)&equal;
        equal = (this->month==x.month)&equal;
        equal = (this->day==x.day)&equal;
        return equal;
    }
    bool operator !=(const Date& x) {
        bool equal = 0;
        equal = (this->year!=x.year)|equal;
        equal = (this->month!=x.month)|equal;
        equal = (this->day!=x.day)|equal;
        return equal;
    }
    bool operator <<(const string dataIn) {
        sscanf(dataIn.c_str(), "%hd-%hd-%hd", &year, &month, &day);
        if(year < 1000 || year > 2100)
            return 0;
        else
            return 1;
    }
};

struct ISBN {
    unsigned group1;
    unsigned group2;
    unsigned group3;
    unsigned group4;
    unsigned group5;
    bool operator ==(const ISBN& x) {
        bool equal = 1;
        equal = (this->group1==x.group1)&equal;
        equal = (this->group2==x.group2)&equal;
        equal = (this->group3==x.group3)&equal;
        equal = (this->group4==x.group4)&equal;
        equal = (this->group5==x.group5)&equal;
        return equal;
    }
    bool operator !=(const ISBN& x) {
        bool equal = 0;
        equal = (this->group1!=x.group1)|equal;
        equal = (this->group2!=x.group2)|equal;
        equal = (this->group3!=x.group3)|equal;
        equal = (this->group4!=x.group4)|equal;
        equal = (this->group5!=x.group5)|equal;
        return equal;
    }
    bool operator <<(const string isbnIn) {
        sscanf(isbnIn.c_str(), "%d-%d-%d-%d-%d", &group1, &group2, &group3, &group4, &group5);
        if(group1 != 978)
            return 0;
        else
            return 1;
    }
};

#endif
