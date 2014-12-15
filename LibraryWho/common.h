//
//  common.h
//  LibraryWho
//
//  Created by Whoami on 14/12/15.
//  Copyright (c) 2014年 Whoami. All rights reserved.
//

#ifndef LibraryWho_common_h
#define LibraryWho_common_h

#include <string>
using namespace std;

struct Date {
    short year;
    short month;
    short day;
};

struct ISBN {
    unsigned group1;
    unsigned group2;
    unsigned group3;
    unsigned group4;
    unsigned group5;
};


#endif
